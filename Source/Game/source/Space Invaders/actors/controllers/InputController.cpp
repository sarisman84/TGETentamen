#include "InputController.h"
#include "../../Entity.h"

#include "../8BitActor.h"
#include "../Actor.h"
#include "../../logistics/collision/Collider.h"
#include "../../logistics/interaction/HealthInteractor.h"

#include "Space Invaders/logistics/ai/EnemyManager.h"
#include "Space Invaders/logistics/ui/CanvasManager.h"
#include "Space Invaders/logistics/scene management/SceneManager.h"

#include "Space Invaders/logistics/ui/canvases/CanvasTypes.h"

#include <tge/engine.h>

#include <iostream>
#include <WinUser.h>

void si::InputController::Awake()
{
	myEntity->myName = "Player";
	myActor = &myEntity->AddComponent<Actor>();
	//myEightBitActor = &myEntity->AddComponent<EightBitActor>();
	auto& col = myEntity->AddComponent<Collider>();
	col.myCollisionLayer = static_cast<unsigned char>(Layer::Player);
	auto& hi = myEntity->AddComponent< HealthInteractor>();
	hi.OnDeathEvent() = [this]()
	{
		WaveManager::Reset();
		SceneManager::LoadScene("mainMenu.json");
		Canvas::ResetTo(CanvasTypes::MainMenu);
		Canvas::TransitionTo(CanvasTypes::SaveScore);
	};

	hi.SetHealth(3);

	col.myCollisionRadius = 15.0f;
	myMovementSpeed = 0.25f;

	myEntity->myTransform.Scale() = { 150.0f, 150.0f };


	myBulletInfo.myColliderRadius = 10.0f;
	myBulletInfo.myDirection = { 0.0f, 1.0f };
	myBulletInfo.myDamage = 1.0f;
	myBulletInfo.myBulletVelocity = 350.0f;
	myBulletInfo.myTexture = L"Textures/shot1.dds";
	myBulletInfo.myOwnerID = myEntity->GetUUID();
	myBulletInfo.myCollisionLayer = static_cast<unsigned char>(Layer::Enemy);
	myFireRate = 0.25f;

	//myEightBitActor->myMovementSpeed = myMovementSpeed;
	myActor->myMovementSpeed = myMovementSpeed * 1000.0f;


	myMagazine = 5;
	myReloadTime = 1.5f;


	myCurrentMagazine = myMagazine;
	myCurrReloadTime = myReloadTime;

}

void si::InputController::Update(const float aDT)
{
	myCurFireRate += aDT;
	//myEightBitActor->myPositionOffset = { 0,0 };
	myActor->myVelocity = { 0,0 };

	if (GetAsyncKeyState((int)Key::Left))
		//myEightBitActor->myPositionOffset = Tga::Vector2f{ -1.0f, 0.0f };
		myActor->myVelocity = Tga::Vector2f(-1.0f, 0.0f);
	if (GetAsyncKeyState((int)Key::Right))
		//myEightBitActor->myPositionOffset = Tga::Vector2f{ 1.0f, 0.0f };
		myActor->myVelocity = Tga::Vector2f(1.0f, 0.0f);

	if (GetAsyncKeyState((int)Key::Space) && myCurFireRate >= myFireRate && myCurrentMagazine > 0)
	{
		myCurrentMagazine--;

		auto pos = myEntity->myTransform.Position();
		myBulletInfo.mySpawnPos = { pos.x, pos.y };
		WeaponSystem::Fire(myEntity->myCurrentScene, myBulletInfo);
		myCurFireRate = 0;
	}
	if (myCurrentMagazine <= 0) //If we are out of ammo, reload
	{
		myReloadFlag = true;
		myCurrReloadTime -= aDT;

		if (myCurrReloadTime <= 0) //if we have finished reloading, refill the magazine.
		{
			myReloadFlag = false;
			myCurrReloadTime = myReloadTime;
			myCurrentMagazine = myMagazine;
		}
	}





	auto pos = myActor->GetNextPosition(); //myEightBitActor->GetNextPosition();
	auto size = myEntity->mySprite.mySize / 2.0f;

	auto engine = Tga::Engine::GetInstance();
	auto res = engine->GetRenderSize();

	if (pos.x - size.x < 0 || pos.x + size.x > res.x)
		//myEightBitActor->myPositionOffset = { 0.0f, 0.0f };
		myActor->myVelocity = Tga::Vector2f(0.0f, 0.0f);

}