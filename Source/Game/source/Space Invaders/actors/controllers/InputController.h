#pragma once
#include "../../Component.h"
#include "../../logistics/WeaponSystem.h"
#include <wtypes.h>

namespace si
{
	class Actor;

	enum class Key : int
	{
		A = 0x41,
		S = 0x53,
		D = 0x44,
		W = 0x57,
		Space = VK_SPACE,
		Escape = VK_ESCAPE,
		P = 0x50
	};

	class InputController : public Component
	{
	public:
		void Init() override;
		void Update(const float aDT) override;
	private: //Movement
		Actor* myActor;
		float myMovementSpeed;
	private: //Weapon Logic
		float myFireRate = 0.25f;
		Bullet myBulletInfo;
		
	};
}