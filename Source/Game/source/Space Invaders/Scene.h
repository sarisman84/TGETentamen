#pragma once
#include <vector>
#include <memory>

#include <tge/sprite/sprite.h>

#include "Entity.h"

namespace Tga
{
	class SpriteDrawer;
	class Engine;
}

namespace si
{
	class Component;
	class Entity;

	class Scene
	{
	public: //Setup
		Scene();
	public: //Core Logic
		void Init();
		void Update(const float aDT);
		void Render();

	public: //Helper Logic/Operations
		void operator +=(Entity* const anEntity);
		void operator +=(const std::initializer_list<Entity*>& aList);
	private:
		void ExecuteComponent(const std::vector<std::shared_ptr<Component>> someComponents, void(*anOnComponentExecute)(const float,Component*), const float aDT = 0);

	private: //Entity Containers
		std::vector<std::shared_ptr<Entity>> myEntities;
		std::vector<Tga::SpriteSharedData> myVisualEntities;

	private: //Logistics
		Tga::SpriteDrawer* myRenderer;
		Tga::Engine* myEngine;
	};
}