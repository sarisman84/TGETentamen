#pragma once
#include "../../Component.h"


#include <functional>

namespace si
{
	class Collider : public Component
	{
	public: //Core
		void Awake() override;
		void Update(const float aDT) override;
		void OnDestroy() override;
	public: //Collision Logic
		const bool TriggerCollisionEvent(Entity* const someOtherEntity);
		const bool HasCollidedWith(Collider* const someOtherCollider);
		const bool HasCollisionEventTriggered();
	public: //Accessors
		inline Entity* const GetEntity() const { return myEntity; }
		inline std::function<void(Entity*)>& OnCollisionEvent() { return myOnCollisionEnterEvent; }
	public:
		float myCollisionRadius = 10.0f;
	private:
		std::function<void(Entity*)> myOnCollisionEnterEvent;
		bool myCollisionState = false;


	};
}