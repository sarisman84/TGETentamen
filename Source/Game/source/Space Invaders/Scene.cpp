#include "Scene.h"
#include "Entity.h"
#include "Component.h"

#include <tge/graphics/GraphicsEngine.h>
#include <tge/drawers/SpriteDrawer.h>
#include <tge/drawers/DebugDrawer.h>
#include <tge/texture/TextureManager.h>
#include <tge/settings/settings.h>

#include <tge/engine.h>


#include "logistics/collision/Collider.h"

#include "logistics/logging/Logger.h"

#pragma warning(disable: 4244)


si::Scene::Scene()
{
	myEngine = Tga::Engine::GetInstance();
	myRenderer = &myEngine->GetGraphicsEngine().GetSpriteDrawer();
}

void si::Scene::Init()
{


	auto& textureManager = myEngine->GetTextureManager();


	for (auto& e : myEntities)
	{
		auto& entity = e.second;
		ExecuteComponent(entity->GetComponents(), [](const float /*aDT*/, Component* aComponent) { aComponent->Init(); });
		myVisualEntities[e.first].myTexture = textureManager.GetTexture(entity->mySprite.mySpritePath);
	}
}

void si::Scene::Update(const float aDT)
{
	if (!myActiveState) return;
	ClearGarbage();

	auto cpy = myEntities;
	for (auto& e : cpy)
	{
		if (!e.second->IsActive()) continue;
		ExecuteComponent(e.second->GetComponents(), [](const float aDT, Component* aComponent) { aComponent->Update(aDT); }, aDT);
	}


}

void si::Scene::Render()
{
	if (!myActiveState) return;
	auto cpy = myVisualEntities;
	for (auto& p : cpy)
	{
		if (!myEntities[p.first]->IsActive()) continue;

		auto& vE = p.second;
		auto& e = myEntities[p.first];
		std::wstring sp(e->mySprite.mySpritePath);
		//LOG("Rendering entity " + std::to_string(p.first) + " with texture: " + std::string(sp.begin(), sp.end()));

		Tga::Sprite2DInstanceData data = {};
		auto pos = e->myTransform.GetPosition();
		auto size = myVisualEntities[p.first].myTexture->CalculateTextureSize();
		data.myPosition = Tga::Vector2f{ pos.x, pos.y };
		e->mySprite.mySize = Tga::Vector2f(static_cast<float>(size.x), static_cast<float>(size.y));
		data.myPivot = e->mySprite.myPivot;
		data.mySize = Tga::Vector2f{ static_cast<float>(size.x), static_cast<float>(size.y) } *myEntities[p.first]->mySprite.mySizeOffset;
		data.myColor = e->mySprite.myColor;

		myRenderer->Draw(vE, data);
	}

#ifndef _RETAIL
	{

		for (auto& pair : myColliders)
		{
			auto& collider = pair.second;
			auto pos = collider->GetEntity()->myTransform.Position();
			Tga::DebugDrawer& dbg = myEngine->GetDebugDrawer();
			dbg.DrawCircle({ pos.x, pos.y }, collider->myCollisionRadius, collider->HasCollisionEventTriggered() ? Tga::Color(0.0f, 1.0f, 0.0f, 1.0f) : Tga::Color(0.75f, 0.75f, 0.75f, 1.0f));
		}

	}
#endif

}


void si::Scene::ExecuteComponent(std::vector<std::shared_ptr<Component>>& someComponents, void(*anOnComponentExecute)(const float, Component*), const float aDT)
{
	for (size_t i = 0; i < someComponents.size(); i++)
	{
		auto& component = someComponents[i];
		anOnComponentExecute(aDT, component.get());
	}
}



uint32_t si::Scene::operator +=(Entity* const anEntity)
{
	uint32_t id = static_cast<uint32_t>(rand());

	myEntities[id] = std::shared_ptr<Entity>(anEntity);
	si::Entity& newEntity = *myEntities[id];
	newEntity.myCurrentScene = this;
	newEntity.myUUID = id;
	newEntity.SetActive(true);

	Tga::SpriteSharedData sharedData = {};
	sharedData.myTexture = myEngine->GetTextureManager().GetTexture(newEntity.mySprite.mySpritePath);
	myVisualEntities[id] = sharedData;

	ExecuteComponent(newEntity.GetComponents(), [](const float /*aDT*/, Component* aComponent)
		{
			aComponent->Awake();
		});

	return id;
}

void si::Scene::operator +=(const std::initializer_list<Entity*>& aList)
{
	for (auto& e : aList)
	{
		(*this) += e;
	}
}

si::Entity* si::Scene::operator[](const uint32_t anID)
{
	return myEntities[anID].get();
}

void si::Scene::MarkForDelete(const uint32_t anUUID)
{
	myGarbageCollection.push_back(anUUID);
}

#ifndef _RETAIL
#include <iostream>
#endif

void si::Scene::ClearGarbage()
{
	for (size_t i = 0; i < myGarbageCollection.size(); i++)
	{


		auto index = myGarbageCollection[i];

		auto& elm = myEntities[index];

		if (elm)
			ExecuteComponent(elm->GetComponents(), [](const float /*aDT*/, Component* aComp)
				{
					aComp->OnDestroy();

				});

		myEntities.erase(index);
		myVisualEntities.erase(index);
		myColliders.erase(index);


		LOG("[System - Garbage Collection] Cleared entity " + std::to_string(index));

		//#ifndef _RETAIL
		//		std::cout << "[LOG][Scene::GarbageCollector]: Cleared entity " << index << "!\n";
		//#endif
	}

	myGarbageCollection.clear();
}

const bool si::Scene::IsActive() const
{
	return myActiveState;
}

void si::Scene::SetActive(const bool aNewState)
{
	myActiveState = aNewState;
}
