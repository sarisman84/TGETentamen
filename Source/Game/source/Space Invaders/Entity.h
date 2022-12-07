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
		Type GetComponent();

		template<typename Type, typename... Args>
		Type AddComponent(Args&&... someArgs);

		inline std::vector<std::shared_ptr<Component>>& GetComponents() { return myComponents; }
	public:
		Tga::Transform myTransform;
		Sprite mySprite;
	private:
		std::vector<std::shared_ptr<Component>> myComponents;
	};
}