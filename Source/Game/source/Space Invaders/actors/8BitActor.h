#pragma once
#include <tge/math/Vector.h>
#include "../Component.h"
namespace si
{
	class EightBitActor : public Component
	{
	public:
		void Update(const float aDT) override;
	public:
		Tga::Vector2f myPositionOffset;
		float myMovementSpeed;
	private:
		float myTempTimer;
		

	};
}