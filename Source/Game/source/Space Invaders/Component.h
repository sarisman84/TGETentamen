#pragma once
#include <memory>

namespace si
{
	class Entity;

	class Component
	{
	public:
		virtual void Init() {};
		virtual void Update(const float /*aDT*/) {};
	protected:
		Entity* myEntity;
	};
}