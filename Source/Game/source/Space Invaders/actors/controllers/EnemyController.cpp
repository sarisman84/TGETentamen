#include "EnemyController.h"
#include "../../Entity.h"
#include "../../Scene.h"
#include "../../logistics/interaction/HealthInteractor.h"
#include "../8BitActor.h"

#include "../../logistics/ai/EnemyManager.h"
#include "../../logistics/WeaponSystem.h"
#include "../../logistics/collision/Collider.h"

void si::EnemyController::Init()
{
	myActor = myEntity->GetComponent<EightBitActor>();
	myHealthInteractor = myEntity->GetComponent<HealthInteractor>();
	
	myGeneralBulletInfo.myCollisionLayer = static_cast<unsigned char>(Layer::Player);

	myFireRate = 3.00f;
	myCurFireRate = myFireRate;
}

void si::EnemyController::Update(const float aDT)
{
	if (!myActor) return;
	myActor->myPositionOffset = WaveManager::GetGroupVelocity();


	if (myActor->GetPreviousPosition().y != myEntity->myTransform.Position().y)
	{
		WaveManager::ResetDecentFlag();
	}

	if (myGeneralBulletInfo.myBulletVelocity == 0) return;

	myCurFireRate -= aDT;

	if (myCurFireRate <= 0)
	{
		auto pos = myEntity->myTransform.Position();
		myGeneralBulletInfo.myDirection = { 0.0f, -1.0f };
		myGeneralBulletInfo.mySpawnPos = Tga::Vector2f(pos.x, pos.y) - Tga::Vector2f(0.0f, (myEntity->mySprite.mySize.y / 2.0f) + 50.0f);
		myGeneralBulletInfo.myOwnerID = myEntity->GetUUID();
		WeaponSystem::Fire(myEntity->myCurrentScene, myGeneralBulletInfo);
		myCurFireRate = myFireRate;
	}
}


const uint32_t si::EnemyController::GetEnemyUUID()
{
	return myEntity->GetUUID();
}
