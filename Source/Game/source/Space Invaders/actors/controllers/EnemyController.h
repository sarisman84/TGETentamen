#pragma once
#include "../../Component.h"
#include "../../logistics/WeaponSystem.h"
namespace si
{
	class HealthInteractor;
	class EnemyController : public Component
	{
	public:
		void Init() override;
	private:
		HealthInteractor* myHealthInteractor;
		Bullet myGeneralBulletInfo;
	};

}

