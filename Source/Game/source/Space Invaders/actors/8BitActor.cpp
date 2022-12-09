#include "8BitActor.h"
#include "../Entity.h"

void si::EightBitActor::Update(const float aDT)
{
	myTempTimer += aDT;
	if (myTempTimer >= myMovementSpeed)
	{
		myEntity->myTransform.Position() += Tga::Vector3f(myPositionOffset.x, myPositionOffset.y, 0.0f);
		myTempTimer = 0;
	}
		
}
