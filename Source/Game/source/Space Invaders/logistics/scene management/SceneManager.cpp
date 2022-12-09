#include "SceneManager.h"
#include "../../Scene.h"
#include "../collision/CollisionManager.h"
#include "../../actors/controllers/InputController.h"

#include <tge/engine.h>
#include <tge/settings/settings.h>

#include <fstream>
#include <nlohmann/json.hpp>

#include <atlbase.h>
#include <atlconv.h>

#include <cassert>


si::SceneManager::SceneManager()
{
	ourInstance = this;
}

void si::SceneManager::RegisterScene(const std::string& aName, Scene* const aNewScene)
{
	ourInstance->mySceneRegistry[aName] = aNewScene;
	ourInstance->myCurrentScene = aName;
}

void si::SceneManager::LoadScene(const std::string& aName)
{
	if (!ourInstance->IsEmpty()) //Disable the previous scene, should one have existed
		ourInstance->CurrentScene()->SetActive(false);
	auto& sceneReg = ourInstance->mySceneRegistry;

	if (sceneReg.empty() || sceneReg.count(aName) == 0)
	{
		ourInstance->LoadSceneFromFile(aName);
	}

	ourInstance->myCurrentScene = aName;
	ourInstance->CurrentScene()->SetActive(true); //Enable the new scene
}

void si::SceneManager::Update(const float aDT)
{
	if (!ourInstance->IsEmpty())
	{
		auto& scene = ourInstance->CurrentScene();
		scene->Update(aDT);
		si::CollisionManager::HandleCollisions(scene);
	}

}

void si::SceneManager::Render()
{
	if (!ourInstance->IsEmpty())
		ourInstance->CurrentScene()->Render();
}

si::Scene* const si::SceneManager::GetCurrentScene()
{
	return ourInstance->CurrentScene();
}




void si::SceneManager::LoadSceneFromFile(const std::string& aPath)
{
	std::string sceneFolder = "Data/Scenes/";
	std::string path = sceneFolder + aPath;
	std::ifstream sceneIfs(Tga::Settings::GetAssetW(path));

	assert(sceneIfs.good() && "Failed to find file");

	using namespace nlohmann;
	auto engine = Tga::Engine::GetInstance();

	json sceneInfo = json::parse(sceneIfs);

	auto newScene = new Scene();

	for (auto& entity : sceneInfo["entities"])
	{
		auto newEntity = new Entity();

		newEntity->mySprite.mySpritePath = std::wstring(CA2W(entity["texture"].get<std::string>().c_str())).c_str();

		auto& ePos = newEntity->myTransform.Position();
		Tga::Vector2f pos;

		json jPos = entity["transform"]["position"];
		json jScale = entity["transform"]["scale"];

		if (jPos.is_string() && jPos.get<std::string>().find("half_screen_size") != std::string::npos)
		{
			pos.x = static_cast<float>(engine->GetRenderSize().x) / 2.0f;
			pos.y = static_cast<float>(engine->GetRenderSize().y) / 2.0f;
		}
		else
		{
			json xCoord = jPos["x"];
			json yCoord = jPos["y"];
			if (xCoord.is_string() && xCoord.get<std::string>().find("half_screen_size") != std::string::npos)
			{
				pos.x = static_cast<float>(engine->GetRenderSize().x) / 2.0f;
			}
			else
			{
				pos.x = xCoord;
			}

			if (yCoord.is_string() && yCoord.get<std::string>().find("half_screen_size") != std::string::npos)
			{
				pos.y = static_cast<float>(engine->GetRenderSize().y) / 2.0f;
			}
			else
			{
				pos.y = yCoord;
			}
		}
		ePos = pos;

		for (auto& comp : entity["components"])
		{
			if (comp["type"] == "InputController")
				newEntity->AddComponent<InputController>();
		}

		(*newScene) += newEntity;

	}

	RegisterScene(aPath, newScene);

}

si::Scene*& si::SceneManager::CurrentScene()
{
	return mySceneRegistry[myCurrentScene];
}

const bool si::SceneManager::IsEmpty() const
{
	return myCurrentScene == "empty";
}


