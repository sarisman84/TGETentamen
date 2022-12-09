#include "EnemyController.h"
#include "../../Entity.h"
#include "../../Scene.h"
#include "../../logistics/interaction/HealthInteractor.h"
#include "../8BitActor.h"

#include "../../logistics/ai/EnemyManager.h"


void si::EnemyController::Init()
{
	myActor = &myEntity->AddComponent<EightBitActor>();
	myHealthInteractor = &myEntity->AddComponent<HealthInteractor>();
	myGeneralBulletInfo.myOwnerID = myEntity->GetUUID();

	//myActor->myMovementSpeed = 
	myHealthInteractor->OnDeathEvent() = [this]() { WaveManager::MarkAsDead(GetEnemyUUID()); };
}

void si::EnemyController::Update(const float /*aDT*/)
{
	myActor->myPositionOffset = WaveManager::GetGroupVelocity();
	
}


const uint32_t si::EnemyController::GetEnemyUUID()
{
	return myEntity->GetUUID();
}
