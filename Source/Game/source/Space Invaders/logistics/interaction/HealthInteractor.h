#pragma once
#include "../../Component.h"

#include <functional>

namespace si
{
	class HealthInteractor : public Component
	{
	public:
		void Init() override;
		void Update(const float aDT) override;
	public:
		void SetHealth(const float aNewMaxHealthVal, const bool aResetCurrentHealthFlag = true);
		void TakeDamage(const float someDamage);
	public:
		inline const float GetCurrentHealth() { return myCurrentHealth; }
		inline const float GetHealth() { return myMaxHealth; }
	private:
		void OnDeath();
	private:
		std::function<void()> myOnDeathEvent;
		float myCurrentHealth;
		float myMaxHealth;
	};
}