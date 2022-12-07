#include "InputController.h"
#include "../../Entity.h"

#include "../Actor.h"

#include <tge/engine.h>

#include <iostream>
#include <WinUser.h>

void si::InputController::Init()
{
	myActor = &myEntity->AddComponent<Actor>();
	myMovementSpeed = 500.0f;

	myEntity->myTransform.Scale() = { 150.0f, 150.0f };

}

void si::InputController::Update(const float /*aDT*/)
{
	std::cout << "\r" << (myActor->IsInRenderView() ? "Can see Actor" : "Cannot see Actor") << std::flush;

	myActor->myVelocity = Tga::Vector2f{ 0.0f, 0.0f };


	if (GetAsyncKeyState((int)Key::A))
		myActor->myVelocity = Tga::Vector2f{ -1.0f, 0.0f } *myMovementSpeed;
	if (GetAsyncKeyState((int)Key::D))
		myActor->myVelocity = Tga::Vector2f{ 1.0f, 0.0f } *myMovementSpeed;

	if (GetAsyncKeyState((int)Key::Space))
		WeaponSystem::Fire({});

	auto pos = myActor->GetNextPosition();
	auto size = myEntity->myTransform.Scale() / 2.0f;

	auto engine = Tga::Engine::GetInstance();
	auto res = engine->GetRenderSize();

	if (pos.x - size.x < 0 || pos.x + size.x > res.x)
		myActor->myVelocity = { 0.0f, 0.0f };

}