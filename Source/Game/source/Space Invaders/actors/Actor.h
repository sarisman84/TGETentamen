#pragma once
#include <tge/math/Vector.h>

#include "../Component.h"

namespace si
{
	class Actor : public Component
	{
	public: //Core
		void Init() override;
		void Update(const float aDT) override;
	public: //Utility
		const bool IsInRenderView() const;
		const Tga::Vector2f GetNextPosition() const;
	public: //Public Variables
		Tga::Vector2f myVelocity;
		float myMovementSpeed;
	
	
	};
}