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
		float myColliderRadius;
		float myDamage;
		const wchar_t* myTexture;
	};


	namespace WeaponSystem
	{
		const bool Fire(Scene* aScene, const Bullet& someInformation);

	}



}
