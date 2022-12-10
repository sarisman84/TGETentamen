#include "8BitActor.h"
#include "../Entity.h"
#include "../logistics/logging/Logger.h"

void si::EightBitActor::Update(const float aDT)
{


	myTempTimer += aDT;
	if (myTempTimer >= myMovementSpeed)
	{
		LOG("Entity " + std::to_string(myEntity->GetUUID()) + "'s position updated! [" + std::to_string(myMovementSpeed) + " speed]");
		myPreviousPosition = { myEntity->myTransform.Position().x, myEntity->myTransform.Position().y };
		myEntity->myTransform.Position() += Tga::Vector3f(myPositionOffset.x, myPositionOffset.y, 0.0f) * myPixelSizeOffset;
		myTempTimer = 0;
	}

}

Tga::Vector2f si::EightBitActor::GetNextPosition()
{
	Tga::Vector2f pos = { myEntity->myTransform.Position().x, myEntity->myTransform.Position().y };
	return pos + Tga::Vector2f(myPositionOffset.x, myPositionOffset.y) * myPixelSizeOffset;
}
