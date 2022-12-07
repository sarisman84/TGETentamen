#pragma once
#include "../../Component.h"
#include <wtypes.h>

namespace si
{
	class Actor;

	enum class Key : int
	{
		A = 0x41,
		S = 0x53,
		D = 0x44,
		W = 0x57,
		Space = VK_SPACE,
		Escape = VK_ESCAPE,
		P = 0x50
	};

	class InputController : public Component
	{
	public:
		void Init() override;
		void Update(const float aDT) override;
	private:
		Actor* myActor;
		float myMovementSpeed;
	};
}