#include "CollisionManager.h"
#include "Collider.h"

#include "../../Scene.h"

void si::CollisionManager::HandleCollisions(Scene* const aScene)
{
	if (!aScene) return;

	auto& colliders = aScene->GetColliders();



	for (auto nextItA = colliders.begin(), itA = nextItA++; nextItA != colliders.end(); ++itA, ++nextItA)
	{
		auto& colliderA = (*itA).second;
		for (auto itB = nextItA; itB != colliders.end(); ++itB)
		{
			auto& colliderB = (*itB).second;

			if (colliderA->HasCollidedWith(colliderB))
			{
				colliderA->TriggerCollisionEvent(colliderB->GetEntity());
				colliderB->TriggerCollisionEvent(colliderA->GetEntity());
			}

		}
	}
}
