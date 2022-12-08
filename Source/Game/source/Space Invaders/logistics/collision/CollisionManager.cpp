#include "CollisionManager.h"
#include "Collider.h"

#include "../../Scene.h"

void si::CollisionManager::HandleCollisions(Scene* const aScene)
{
	if (!aScene) return;

	auto& colliders = aScene->GetColliders();
	for (auto& aPair : colliders)
	{
		auto& colliderA = aPair.second;
		for (auto& bPair : colliders)
		{
			if (aPair.first == bPair.first) continue;

			auto& colliderB = bPair.second;

			if (colliderA->HasCollidedWith(colliderB))
			{
				colliderA->TriggerCollisionEvent(colliderB->GetEntity());
				colliderB->TriggerCollisionEvent(colliderA->GetEntity());
			}

		}
	}
}
