#pragma once
#include <vector>

#include <tge/math/Vector.h>

namespace si
{
	class Scene;

	struct Bullet
	{
		uint32_t myOwnerID;
		Tga::Vector2f mySpawnPos;
		Tga::Vector2f myDirection;
		float myBulletVelocity;
		float myColliderRadius;
		float myDamage;
		const wchar_t* myTexture;
		unsigned char myCollisionLayer = 1; //Default layer
	};


	namespace WeaponSystem
	{
		const bool Fire(Scene* aScene, const Bullet& someInformation);

	}



}
