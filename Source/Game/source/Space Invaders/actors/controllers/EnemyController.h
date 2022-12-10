#pragma once
#include "../../Component.h"
#include "../../logistics/WeaponSystem.h"
namespace si
{
	class EightBitActor;
	class HealthInteractor;
	class EnemyController : public Component
	{
	public:
		void Init() override;
		void Update(const float aDT) override;
	public:
		inline Bullet& WeaponInfo() { return myGeneralBulletInfo; }
		inline HealthInteractor*& HealthInfo() { return myHealthInteractor; }

		inline float& MovementSpeed() { myInitMovementSpeed; }
		const uint32_t GetEnemyUUID();
	private:
		float myInitMovementSpeed;
	private:
		EightBitActor* myActor;
		HealthInteractor* myHealthInteractor;
		Bullet myGeneralBulletInfo;
		uint32_t myEnemyID;

	};

}

