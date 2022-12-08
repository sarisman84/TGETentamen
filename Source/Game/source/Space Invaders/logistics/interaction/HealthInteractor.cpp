#include "HealthInteractor.h"
#include "../../Entity.h"
#include "../../Scene.h"

void si::HealthInteractor::Init()
{
	myCurrentHealth = myMaxHealth;
}



void si::HealthInteractor::Update(const float /*aDT*/)
{

}

void si::HealthInteractor::SetHealth(const float aNewMaxHealthVal, const bool aResetCurrentHealthFlag)
{
	myMaxHealth = aNewMaxHealthVal;

	if (aResetCurrentHealthFlag)
		myCurrentHealth = myMaxHealth;
}

void si::HealthInteractor::TakeDamage(const float someDamage)
{
	if (myMaxHealth < 0) return; //Can be used to cheat for debugging purposes

	myCurrentHealth -= someDamage;

	if (myCurrentHealth <= 0)
	{
		OnDeath();
	}
}

void si::HealthInteractor::OnDeath()
{
	if (myOnDeathEvent)
		myOnDeathEvent();

	myEntity->myCurrentScene->MarkForDelete(myEntity->GetUUID());
}
