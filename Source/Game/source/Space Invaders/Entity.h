#pragma once
#include <vector>
#include <memory>

#include <tge/math/Transform.h>


#include "rendering/Sprite.h"

namespace si
{
	class Component;

	class Entity
	{
	public:
		template<typename Type>
		Type& GetComponent();

		template<typename Type, typename... Args>
		Type& AddComponent(Args&&... someArgs);

		inline std::vector<std::shared_ptr<Component>>& GetComponents() { return myComponents; }
	public:
		Tga::Transform myTransform;
		Sprite mySprite;
	private:
		std::vector<std::shared_ptr<Component>> myComponents;
	};




#pragma region Member Definitions
	template<typename Type>
	inline Type& Entity::GetComponent()
	{
		auto& it = std::find_if(myComponents.begin(), myComponents.end(), [](std::shared_ptr<Component>& aComponent)
			{
				if (std::dynamic_pointer_cast<Type>(aComponent))
					return true;
				return false;
			});


		if (it == myComponents.end()) return Type();
		return *std::dynamic_pointer_cast<Type>((*it));
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