#include "EnemyFactory.h"
#include "../../enemy/EnemyInfo.h"
#include "../scene management/SceneManager.h"
#include "../../Scene.h"

#include "../../actors/8BitActor.h"
#include "../../actors/controllers/EnemyController.h"
#include "../interaction/HealthInteractor.h"
#include "../collision/Collider.h"
#include "../../Entity.h"
#include "../ai/EnemyManager.h"

si::EnemyFactory::EnemyFactory()
{
	ourInstance = this;
	EnemyBlueprint type1;
	type1.myTexture = L"Textures/enemy1.dds";
	type1.myHealthAmm = 1;
	AddType(EnemyID::Tier0, type1);


	EnemyBlueprint type2;
	type2.myTexture = L"Textures/enemy2.dds";
	type2.myHealthAmm = 2;
	type2.myFireRate = 0.75f;
	type2.myBulletTexture = L"Textures/shot2.dds";
	type2.myBulletSpeed = 150.0f;
	type2.myBulletFireDir = Tga::Vector2f(0.0f, -1.0f);
	type2.myBulletDamage = 1.0f;
	type2.myBulletCollisionRadius = 45.0f;
	type2.myPointAmm = 20.0f;
	AddType(EnemyID::Tier1, type2);

	EnemyBlueprint type3;
	type3.myTexture = L"Textures/enemy3.dds";
	type3.myHealthAmm = 3;
	type3.myFireRate = 0.5f;
	type3.myBulletTexture = L"Textures/shot2.dds";
	type3.myBulletSpeed = 175.0f;
	type3.myBulletFireDir = Tga::Vector2f(0.0f, -1.0f);
	type3.myBulletDamage = 1.0f;
	type3.myBulletCollisionRadius = 30.0f;
	type3.myPointAmm = 40.0f;
	AddType(EnemyID::Tier2, type3);

}

void si::EnemyFactory::AddType(const uint32_t anID, const EnemyBlueprint& aNewBlueprint)
{
	myTypes[anID] = aNewBlueprint;
}

si::Entity* const si::EnemyFactory::GetEnemy(const uint32_t anEnemyType)
{
	if (myTypes.count(anEnemyType) == 0) return nullptr;

	auto& type = myTypes[anEnemyType];

	auto newEnemy = new Entity();
	newEnemy->mySprite.mySpritePath = type.myTexture;
	newEnemy->mySprite.mySizeOffset = { 1,1 };
	auto& enemyController = newEnemy->AddComponent<EnemyController>();
	auto& healthInteractor = newEnemy->AddComponent<HealthInteractor>();
	auto& actor = newEnemy->AddComponent<EightBitActor>();
	auto& collider = newEnemy->AddComponent<Collider>();
	auto& bullet = enemyController.WeaponInfo();

	collider.myCollisionRadius = 45.0f;

	bullet.myColliderRadius = type.myBulletCollisionRadius;
	bullet.myDamage = type.myBulletDamage;
	bullet.myDirection = type.myBulletFireDir * type.myBulletSpeed;
	bullet.myTexture = type.myBulletTexture;

	healthInteractor.SetHealth(type.myHealthAmm);
	healthInteractor.OnDeathEvent() = [newEnemy, type]()
	{
		WaveManager::MarkAsDead(newEnemy->GetUUID());
		ScoreSystem::IncrementScore(static_cast<uint32_t>(type.myPointAmm));
	};

	actor.myMovementSpeed = 1.5f;

	for (auto& comp : newEnemy->GetComponents())
	{
		comp->Init();
	}

	return newEnemy;
}
