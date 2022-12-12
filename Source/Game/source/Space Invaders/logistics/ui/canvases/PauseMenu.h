#pragma once
#include "../framework/UICanvas.h"
namespace si
{
	class PauseMenu : public UICanvas
	{
		void OnTransitionEnter() override;
		void OnUpdate(const float aDT) override;
	private:
		float myCurDelay;
		float myDelay = 0.5f;

		bool myInputDelayTrigger = false;
	};
}