#pragma once
#include "../framework/UICanvas.h"
namespace si 
{
	class InGameHUD : public UICanvas
	{
	public:
		void OnTransitionEnter() override;
		void OnUpdate(const float aDT) override;
	private:
		float myDelay = 0.25f;
		float myCurDelay;
	};

}