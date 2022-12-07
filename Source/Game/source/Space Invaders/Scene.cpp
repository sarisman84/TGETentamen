#include "Scene.h"
#include "Entity.h"
#include "Component.h"

#include <tge/graphics/GraphicsEngine.h>
#include <tge/drawers/SpriteDrawer.h>
#include <tge/texture/TextureManager.h>
#include <tge/settings/settings.h>

#include <tge/engine.h>



si::Scene::Scene() = default;

void si::Scene::Init()
{
	myEngine = Tga::Engine::GetInstance();
	myRenderer = &myEngine->GetGraphicsEngine().GetSpriteDrawer();

	auto& textureManager = myEngine->GetTextureManager();

	myVisualEntities.resize(myEntities.size());

	for (size_t i = 0; i < myEntities.size(); i++)
	{
		ExecuteComponent(myEntities[i]->GetComponents(), [](const float /*aDT*/, Component* aComponent) { aComponent->Init(); });
		myVisualEntities[i].myTexture = textureManager.GetTexture(myEntities[i]->mySprite.mySpritePath);
	}
}

void si::Scene::Update(const float aDT)
{
	for (size_t i = 0; i < myEntities.size(); i++)
	{
		ExecuteComponent(myEntities[i]->GetComponents(), [](const float aDT, Component* aComponent) { aComponent->Update(aDT); }, aDT);
	}
}

void si::Scene::Render()
{
	for (size_t i = 0; i < myVisualEntities.size(); i++)
	{
		Tga::Sprite2DInstanceData data = {};
		auto pos = myEntities[i]->myTransform.GetPosition();
		auto size = myVisualEntities[i].myTexture->CalculateTextureSize();
		data.myPosition = Tga::Vector2f{ pos.x, pos.y };
		myEntities[i]->mySprite.mySize = Tga::Vector2f(static_cast<float>(size.x), static_cast<float>(size.y));
		data.myPivot = myEntities[i]->mySprite.myPivot;
		data.mySize = myEntities[i]->mySprite.mySizeOffset + Tga::Vector2f{ static_cast<float>(size.x), static_cast<float>(size.y) };
		data.myColor = myEntities[i]->mySprite.myColor;

		myRenderer->Draw(myVisualEntities[i], data);
	}
}


void si::Scene::ExecuteComponent(const std::vector<std::shared_ptr<Component>> someComponents, void(*anOnComponentExecute)(const float, Component*), const float aDT)
{
	for (size_t i = 0; i < someComponents.size(); i++)
	{
		auto& component = someComponents[i];
		anOnComponentExecute(aDT, component.get());
	}
}



void si::Scene::operator +=(Entity* const anEntity)
{
	myEntities.push_back(std::shared_ptr<Entity>(anEntity));
	si::Entity& newEntity = *myEntities.back();

	Tga::SpriteSharedData sharedData = {};
	sharedData.myTexture = myEngine->GetTextureManager().GetTexture(newEntity.mySprite.mySpritePath);
	myVisualEntities.push_back(sharedData);

	ExecuteComponent(newEntity.GetComponents(), [](const float /*aDT*/, Component* aComponent) 
		{ 
			aComponent->Init(); 
		});
}

void si::Scene::operator +=(const std::initializer_list<Entity*>& aList)
{
	for (auto& e : aList)
	{
		(*this) += e;
	}
}
