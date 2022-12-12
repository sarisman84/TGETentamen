#pragma once
#include <vector>
#include <unordered_map>
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
	class UIContent;
	class Collider;
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
		uint32_t operator +=(Entity* const anEntity);
		void operator +=(const std::initializer_list<Entity*>& aList);
		Entity* operator[](const uint32_t anID);

		void MarkForDelete(const uint32_t anUUID);
		void ClearGarbage();
		void OnUnload();

		template<typename Type>
		Type* SearchForComponent();

		template<typename Type>
		const bool Contains();

	public: //State Managemnet
		const bool IsActive() const;
		void SetActive(const bool aNewState);
		void SetUpdateActive(const bool aNewState);
		void SetRenderActive(const bool aNewState);
	public: //Accessors
		std::unordered_map<uint32_t, Collider*>& GetColliders() { return myColliders; }
	private:

		void ExecuteComponent(std::vector<std::shared_ptr<Component>>& someComponents, void(*anOnComponentExecute)(const float, Component*), const float aDT = 0);

	private: //Entity Containers
		std::vector<uint32_t> myGarbageCollection;
		std::unordered_map<uint32_t, std::shared_ptr<Entity>> myEntities;
		std::unordered_map<uint32_t, Tga::SpriteSharedData> myVisualEntities;
		std::unordered_map<uint32_t, Collider*> myColliders;

	private: //Logistics
		Tga::SpriteDrawer* myRenderer;
		Tga::Engine* myEngine;
	private: //Other
		bool myUpdateState;
		bool myRenderState;
	};

	template<typename Type>
	inline Type* Scene::SearchForComponent()
	{
		for (auto& entity : myEntities)
		{
			if (auto comp = entity.second->GetComponent<Type>())
				return comp;
		}
		return nullptr;
	}
	template<typename Type>
	inline const bool Scene::Contains()
	{
		for (auto& entity : myEntities)
		{
			if (entity.second->GetComponent<Type>())
				return true;
		}
		return false;
	}
}