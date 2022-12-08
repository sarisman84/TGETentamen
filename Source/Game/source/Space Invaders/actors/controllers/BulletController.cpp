#include "BulletController.h"
#include "../../Entity.h"
#include "../Actor.h"
#include "../../logistics/collision/Collider.h"
#include "../../Scene.h"

#include <tge/engine.h>

void si::BulletController::Awake()
{
	myActor = &myEntity->AddComponent<Actor>();
	//myCollider = &myEntity->AddComponent<Collider>();

	myCollider = myEntity->GetComponent<Collider>();

	myCollider->OnCollisionEvent() = [this](Entity* someOtherEntity)
	{
		if (someOtherEntity->GetUUID() == myOwnerID) return;
		DestroySelf();
	};
}

void si::BulletController::Update(const float /*aDT*/)
{
	auto engine = Tga::Engine::GetInstance();
	myActor->myVelocity = myVelocity;

	if (myActor->GetNextPosition().y >= engine->GetRenderSize().y)
	{
		DestroySelf();
	}
}

void si::BulletController::SetDirection(const Tga::Vector2f& aDirection)
{
	myVelocity = aDirection;
}

void si::BulletController::DestroySelf()
{
	myEntity->myCurrentScene->MarkForDelete(myEntity->GetUUID());
}
