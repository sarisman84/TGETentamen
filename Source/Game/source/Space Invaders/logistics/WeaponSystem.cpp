#include "WeaponSystem.h"
#include "../Scene.h"
#include "../Entity.h"
#include "../actors/controllers/BulletController.h"
#include "../logistics/collision/Collider.h"

const bool si::WeaponSystem::Fire(Scene* aScene, const Bullet& someInformation)
{
	auto entity = new Entity();
	entity->myTransform.Position() = someInformation.mySpawnPos;
	entity->mySprite.mySpritePath = someInformation.myTexture;
	entity->mySprite.mySizeOffset = { 1,1 };
	auto bc = &entity->AddComponent<BulletController>();


	bc->SetOwnerID(someInformation.myOwnerID);
	bc->SetDirection(someInformation.myDirection);
	bc->SetDamage(someInformation.myDamage);

	auto col = &entity->AddComponent<Collider>();
	col->myCollisionRadius = someInformation.myColliderRadius;
	bc->RegisterCollider(col);

	(*aScene) += entity;

	return true;
}
