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
		Tga::Vector2f GetNextPosition();
		inline Tga::Vector2f GetPreviousPosition() { return myPreviousPosition; }
	public:
		Tga::Vector2f myPositionOffset;
		Tga::Vector2f myPreviousPosition;
		float myMovementSpeed;
	private:
		const float myPixelSizeOffset = 50.0f;
		float myTempTimer;


	};
}