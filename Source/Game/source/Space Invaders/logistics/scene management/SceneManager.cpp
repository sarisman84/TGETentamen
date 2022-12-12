#include "SceneManager.h"
#include "../../Scene.h"
#include "../collision/CollisionManager.h"
#include "../../actors/controllers/InputController.h"
#include "../logging/Logger.h"

#include <Space Invaders/logistics/interaction/HealthInteractor.h>
#include <Space Invaders/logistics/collision/Collider.h>

#include <tge/engine.h>
#include <tge/settings/settings.h>

#include <fstream>
#include <nlohmann/json.hpp>

#include <atlbase.h>
#include <atlconv.h>

#include <cassert>
#include <filesystem>


#include <string>
#include <Windows.h>


#pragma warning(disable: 4267)

si::SceneManager::SceneManager()
{
	ourInstance = this;
}

void si::SceneManager::RegisterScene(const std::string& aName, Scene* const aNewScene, const bool /*aRegisterAsUIFlag*/)
{
	std::string key = aName;
	ourInstance->mySceneRegistry[key] = aNewScene;
}

void si::SceneManager::LoadScene(const std::string& aName, const bool aFullLoadFlag)
{
	Scene* oldScene = nullptr;
	if (!ourInstance->IsEmpty())//Disable the previous scene, should one have existed
	{
		
		oldScene = ourInstance->CurrentScene();
		oldScene->OnUnload();
		oldScene->SetActive(false);
	}

	auto& sceneReg = ourInstance->mySceneRegistry;

	if (aFullLoadFlag || sceneReg.empty() || sceneReg.count(aName) == 0)
	{
		ourInstance->LoadSceneFromFile(aName);
	}

	
	ourInstance->myCurrentScene = aName;
	ourInstance->CurrentScene()->SetActive(true); //Enable the new scene

}

void si::SceneManager::Update(const float aDT)
{
	if (!ourInstance) return;

	for (auto& pair : ourInstance->mySceneRegistry)
	{
		auto& scene = pair.second;
		scene->Update(aDT);
	}
	si::CollisionManager::HandleCollisions(ourInstance->GetCurrentScene());

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




std::wstring ToWideChar(const std::string& aVal)
{
	size_t count = MultiByteToWideChar(CP_ACP, 0, aVal.c_str(), aVal.length(), NULL, 0);
	std::wstring wstr(count, 0);
	MultiByteToWideChar(CP_ACP, 0, aVal.c_str(), aVal.length(), &wstr[0], count);
	return wstr;
}

void si::SceneManager::LoadSceneFromFile(const std::string& aPath)
{
	std::string sceneFolder = "Data/Scenes/";
	std::string path = sceneFolder + aPath;
	std::ifstream sceneIfs(Tga::Settings::GetAssetW(path));

	if (sceneIfs.bad())
	{
		ERROR_LOG("Could not find scene " + aPath + " at " + sceneFolder);
		return;
	}
	/*assert(sceneIfs.good() && "Failed to find file");*/

	using namespace nlohmann;
	auto engine = Tga::Engine::GetInstance();

	json sceneInfo = json::parse(sceneIfs);

	auto newScene = new Scene();

	for (auto& entity : sceneInfo["entities"])
	{
		auto newEntity = new Entity();



		auto p = ToWideChar(entity["texture"].get<std::string>());
		newEntity->mySprite.mySpritePath = p.c_str();
		LOG("Attempting to load texture: " + entity["texture"].get<std::string>());
		auto& ePos = newEntity->myTransform.Position();
		newEntity->mySprite.mySizeOffset = Tga::Vector2f(entity["transform"]["scale"]["x"], entity["transform"]["scale"]["y"]);


		{
			Tga::Vector2f pos;
			json jPos = entity["transform"]["position"];

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
		}




		for (auto& comp : entity["components"])
		{
			if (comp["type"] == "InputController")
				newEntity->AddComponent<InputController>();
			if (comp["type"] == "HealthInteractor")
			{
				auto& hi = newEntity->AddComponent<HealthInteractor>();
				hi.SetHealth(comp["data"]["durability"]);
				auto& col = newEntity->AddComponent<Collider>();
				col.myCollisionLayer = static_cast<unsigned char>(comp["data"]["layer"]);
				col.myCollisionRadius = comp["data"]["hitboxRange"];
			}
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




