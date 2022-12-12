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
	if ((*aScene)[someInformation.myOwnerID] && (*aScene)[someInformation.myOwnerID]->myName)
	{
		std::string ownerName((*aScene)[someInformation.myOwnerID]->myName);
		entity->myName = std::string("Bullet [" + ownerName + "]").c_str();
	}
	else
	{
		entity->myName = "Bullet";
	}

	auto bc = &entity->AddComponent<BulletController>();

	bc->SetVelocity(someInformation.myBulletVelocity);
	bc->SetOwnerID(someInformation.myOwnerID);
	bc->SetDirection(someInformation.myDirection);
	bc->SetDamage(someInformation.myDamage);


	auto col = &entity->AddComponent<Collider>();
	col->myCollisionRadius = someInformation.myColliderRadius;
	col->myCollisionLayer = someInformation.myCollisionLayer;
	col->myCollisionLayer |= static_cast<uint32_t>(Layer::Shelter);
	bc->RegisterCollider(col);

	(*aScene) += entity;

	return true;
}
