#include "EnemyController.h"
#include "../../Entity.h"
#include "../../Scene.h"
#include "../../logistics/interaction/HealthInteractor.h"



void si::EnemyController::Init()
{
	myHealthInteractor = &myEntity->AddComponent<HealthInteractor>();

	myGeneralBulletInfo.myDirection = Tga::Vector2f(0.0f, -150.0f);
	myGeneralBulletInfo.myOwnerID = myEntity->GetUUID();
	myGeneralBulletInfo.myColliderRadius = 45.0f;
	myGeneralBulletInfo.myDamage = 1.0f;
}
