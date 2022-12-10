#include "InputController.h"
#include "../../Entity.h"

#include "../8BitActor.h"
#include "../Actor.h"
#include "../../logistics/collision/Collider.h"
#include "../../logistics/interaction/HealthInteractor.h"
#include <tge/engine.h>

#include <iostream>
#include <WinUser.h>

void si::InputController::Awake()
{
	myActor = &myEntity->AddComponent<EightBitActor>();
	auto& col = myEntity->AddComponent<Collider>();
	auto& hi = myEntity->AddComponent< HealthInteractor>();

	hi.SetHealth(1);

	col.myCollisionRadius = 45.0f;
	myMovementSpeed = 0.25f;

	myEntity->myTransform.Scale() = { 150.0f, 150.0f };


	myBulletInfo.myColliderRadius = 10.0f;
	myBulletInfo.myDirection = { 0.0f, 150.0f };
	myBulletInfo.myDamage = 1.0f;
	myBulletInfo.myTexture = L"Textures/shot1.dds";
	myBulletInfo.myOwnerID = myEntity->GetUUID();
	myFireRate = 0.25f;

	myActor->myMovementSpeed = myMovementSpeed;


}

void si::InputController::Update(const float aDT)
{
	myCurFireRate += aDT;
	myActor->myPositionOffset = { 0,0 };


	if (GetAsyncKeyState((int)Key::A))
		myActor->myPositionOffset = Tga::Vector2f{ -1.0f, 0.0f };
	if (GetAsyncKeyState((int)Key::D))
		myActor->myPositionOffset = Tga::Vector2f{ 1.0f, 0.0f };

	if (GetAsyncKeyState((int)Key::Space) && myCurFireRate >= myFireRate)
	{
		auto pos = myEntity->myTransform.Position();
		myBulletInfo.mySpawnPos = { pos.x, pos.y };
		WeaponSystem::Fire(myEntity->myCurrentScene, myBulletInfo);
		myCurFireRate = 0;
	}


	auto pos = myActor->GetNextPosition();
	auto size = myEntity->mySprite.mySize / 2.0f;

	auto engine = Tga::Engine::GetInstance();
	auto res = engine->GetRenderSize();

	if (pos.x - size.x < 0 || pos.x + size.x > res.x)
		myActor->myPositionOffset = { 0.0f, 0.0f };

}