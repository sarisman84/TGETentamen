#pragma once
#include <tge/math/Vector.h>
#include "../../Component.h"

namespace si
{
	class Collider;
	class Actor;
	class BulletController : public Component
	{
	public:
		void Awake() override;
		void Update(const float aDT) override;
	public:
		void SetDirection(const Tga::Vector2f& aDirection);
		inline Collider* const GetCollider() { return myCollider; }
		inline void SetDamage(const float aDamageVal) { myDamage = aDamageVal; }
		inline void SetOwnerID(const uint32_t anID) { myOwnerID = anID; }
		inline void RegisterCollider(Collider* aNewCollider) { myCollider = aNewCollider; }
	private:
		void DestroySelf();
	private:
		Collider* myCollider;
		Actor* myActor;
	private:
		float myDamage;
		Tga::Vector2f myVelocity;
		uint32_t myOwnerID;


	};
}


