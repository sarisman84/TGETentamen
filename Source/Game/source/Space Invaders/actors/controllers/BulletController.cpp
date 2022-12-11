#include "BulletController.h"
#include "../../Entity.h"
#include "../Actor.h"
#include "../../logistics/collision/Collider.h"
#include "../../logistics/interaction/HealthInteractor.h"
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

		if (someOtherEntity->GetComponent<BulletController>()) return;

		if (auto interactor = someOtherEntity->GetComponent<HealthInteractor>())
			interactor->TakeDamage(myDamage);

		DestroySelf();
	};
}

void si::BulletController::Update(const float /*aDT*/)
{
	auto engine = Tga::Engine::GetInstance();
	myActor->myVelocity = myVelocity;
	myActor->myMovementSpeed = myMovementSpeed;

	if (myActor->GetNextPosition().y >= engine->GetRenderSize().y)
	{
		DestroySelf();
	}
}

void si::BulletController::SetDirection(const Tga::Vector2f& aDirection)
{
	myVelocity = aDirection;
}

void si::BulletController::SetVelocity(const float aVelocity)
{
	myMovementSpeed = aVelocity;
}

void si::BulletController::DestroySelf()
{
	myEntity->myCurrentScene->MarkForDelete(myEntity->GetUUID());
}
