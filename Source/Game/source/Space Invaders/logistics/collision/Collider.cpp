#include "Collider.h"
#include "../../Entity.h"
#include "../../Scene.h"
#include "../logging/Logger.h"

void si::Collider::Awake()
{
	myEntity->myCurrentScene->GetColliders()[myEntity->GetUUID()] = this;
}

void si::Collider::Update(const float /*aDT*/)
{
	myCollisionState = false;
}


void si::Collider::OnDestroy()
{
}

const bool si::Collider::TriggerCollisionEvent(Entity* const someOtherEntity)
{
	if (myOnCollisionEnterEvent)
		myOnCollisionEnterEvent(someOtherEntity);
	myCollisionState = true;
	return true;
}

const bool si::Collider::HasCollidedWith(Collider* const someOtherCollider)
{
	const auto everything = static_cast<uint32_t>(Layer::Everything);

	bool isLayersEqual = (someOtherCollider->myCollisionLayer & myCollisionLayer) == myCollisionLayer;
	bool isValid = (someOtherCollider->myCollisionLayer & everything) == everything || isLayersEqual;
	

	if (!isValid) return false;
	/*if (myEntity->myName)
		LOG("Entity '" + std::string(myEntity->myName) + "' has" + (isValid ? " collided " : " not collided") + ".");*/
	//Check taken from this: https://developer.mozilla.org/en-US/docs/Games/Techniques/2D_collision_detection

	auto selfPos = myEntity->myTransform.GetPosition();
	auto otherPos = someOtherCollider->myEntity->myTransform.GetPosition();

	const float dx = selfPos.x - otherPos.x;
	const float dy = selfPos.y - otherPos.y;

	const float dist = std::sqrt((dx * dx) + (dy * dy));

	return dist < myCollisionRadius + someOtherCollider->myCollisionRadius;


}

const bool si::Collider::HasCollisionEventTriggered()
{
	return myCollisionState;
}
