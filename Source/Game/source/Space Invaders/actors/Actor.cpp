#include "Actor.h"
#include "../Entity.h"

#include <tge/engine.h>

#include <iostream>

void si::Actor::Init()
{

}


void si::Actor::Update(const float aDT)
{
	myEntity->myTransform.Position() += Tga::Vector3f(myVelocity.x, myVelocity.y, 0.0f) * myMovementSpeed * aDT;
}

const bool si::Actor::IsInRenderView() const
{
	if (!myEntity) return false;

	auto engine = Tga::Engine::GetInstance();
	auto resolution = engine->GetRenderSize();
	auto pos = myEntity->myTransform.Position();
	auto size = myEntity->mySprite.mySize;

	auto halfExtends = size / 2.0f;

	return 
		pos.x + halfExtends.x > 0 && 
		pos.y + halfExtends.y > 0 && 
		pos.x - halfExtends.x < resolution.x && 
		pos.y - halfExtends.y < resolution.y;

}

const Tga::Vector2f si::Actor::GetNextPosition() const
{
	auto engine = Tga::Engine::GetInstance();
	Tga::Vector3f pos = myEntity->myTransform.Position() + Tga::Vector3f(myVelocity.x, myVelocity.y, 0.0f) * myMovementSpeed * engine->GetDeltaTime();
	return { pos.x, pos.y };
}
