#pragma once
#include <memory>

namespace si
{
	class Entity;

	class Component
	{
		friend Entity;
	public:
		virtual void Init() {};
		virtual void Awake() {};
		virtual void Update(const float /*aDT*/) {};
		virtual void OnDestroy() {};
	protected:
		Entity* myEntity = nullptr;
	};
}