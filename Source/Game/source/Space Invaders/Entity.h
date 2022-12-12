#pragma once
#include <vector>
#include <memory>

#include <tge/math/Transform.h>


#include "rendering/Sprite.h"

namespace si
{
	class Component;
	class Scene;

	class Entity
	{
		friend Scene;
	public:

		template<typename Type>
		Type* GetComponent();

		template<typename Type, typename... Args>
		Type& AddComponent(Args&&... someArgs);

		inline std::vector<std::shared_ptr<Component>>& GetComponents() { return myComponents; }

		inline void SetActive(const bool aNewState) { myActiveState = aNewState; }
		inline const bool IsActive() const { return myActiveState; }

		inline const uint32_t GetUUID() { return myUUID; }

		const bool IsInRenderView() ;

	public:
		inline const bool operator==(const Entity& someOther) {
			return myUUID == someOther.myUUID;
		}
	public:
		Tga::Transform myTransform;
		Sprite mySprite;
		Scene* myCurrentScene;
		const char* myName;
	private:
		uint32_t myUUID;
		std::vector<std::shared_ptr<Component>> myComponents;
		bool myActiveState;
	};




#pragma region Member Definitions
	template<typename Type>
	inline Type* Entity::GetComponent()
	{
		auto it = std::find_if(myComponents.begin(), myComponents.end(), [](std::shared_ptr<Component>& aComponent)
			{
				if (std::dynamic_pointer_cast<Type>(aComponent))
					return true;
				return false;
			});


		if (it == myComponents.end()) return nullptr;
		return std::dynamic_pointer_cast<Type>((*it)).get();
	}


	template<typename Type, typename ...Args>
	inline Type& si::Entity::AddComponent(Args && ...someArgs)
	{
		myComponents.push_back(std::make_shared<Type>(someArgs...));

		auto& comp = myComponents.back();
		comp->myEntity = this;
		return *std::dynamic_pointer_cast<Type>(comp);
	}

#pragma endregion
}