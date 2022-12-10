#include "EnemyController.h"
#include "../../Entity.h"
#include "../../Scene.h"
#include "../../logistics/interaction/HealthInteractor.h"
#include "../8BitActor.h"

#include "../../logistics/ai/EnemyManager.h"


void si::EnemyController::Init()
{
	myActor = myEntity->GetComponent<EightBitActor>();
	myHealthInteractor = myEntity->GetComponent<HealthInteractor>();
	myGeneralBulletInfo.myOwnerID = myEntity->GetUUID();
}

void si::EnemyController::Update(const float /*aDT*/)
{
	if (!myActor) return;
	myActor->myPositionOffset = WaveManager::GetGroupVelocity();

	if (myActor->GetPreviousPosition().y != myEntity->myTransform.Position().y) 
	{
		WaveManager::ResetDecentFlag();
	}
}


const uint32_t si::EnemyController::GetEnemyUUID()
{
	return myEntity->GetUUID();
}
