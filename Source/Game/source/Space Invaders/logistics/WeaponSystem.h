#pragma once
#include <vector>

#include <tge/math/Vector.h>

namespace si
{
	struct Bullet
	{
		Tga::Vector2f myDirection;
		float myColliderRadius;
		float myDamage;
		const wchar_t* myTexture;
	};


	class WeaponSystem
	{
	public:
		static const bool Fire(const Bullet& someInformation);
	private:

	};
}
