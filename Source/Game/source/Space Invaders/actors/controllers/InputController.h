#pragma once
#include "../../Component.h"
#include "../../logistics/WeaponSystem.h"
#include <wtypes.h>

namespace si
{
	class EightBitActor;
	class Actor;

	enum class Key : int
	{
		Left = VK_LEFT,
		Down = VK_UP,
		Right = VK_RIGHT,
		Up = VK_DOWN,
		Space = VK_SPACE,
		Escape = VK_ESCAPE,
		P = 0x50
	};

	class InputController : public Component
	{
	public:
		void Awake() override;
		void Update(const float aDT) override;
	public:
		inline const int GetCurrentAmmo() { return myCurrentMagazine; }
		inline const bool IsReloading() { return myReloadFlag; }
	private: //Movement
		EightBitActor* myEightBitActor;
		Actor* myActor;
		float myMovementSpeed;
	private: //Weapon Logic
		float myFireRate = 0.25f;
		float myCurFireRate = 0.0f;
		Bullet myBulletInfo;

		int myMagazine;
		float myReloadTime;

		int myCurrentMagazine;
		float myCurrReloadTime;
	private: //States
		bool myReloadFlag;

	};
}