#include "CollisionManager.h"
#include "Collider.h"

#include "../../Scene.h"

void si::CollisionManager::HandleCollisions(Scene* const aScene)
{
	if (!aScene) return;

	auto& colliders = aScene->GetColliders();
	for (size_t a = 0; a < colliders.size(); a++)
	{
		auto& colliderA = colliders[a];
		for (size_t b = a + 1; b < colliders.size(); b++)
		{
			auto& colliderB = colliders[b];

			if (colliderA->HasCollidedWith(colliderB))
			{
				colliderA->TriggerCollisionEvent(colliderB->GetEntity());
				colliderB->TriggerCollisionEvent(colliderA->GetEntity());
			}

		}
	}
}
