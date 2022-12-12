#pragma once
#include "../framework/UICanvas.h"
namespace si
{
	class MainMenu : public UICanvas
	{
		void OnTransitionEnter() override;
		void OnUpdate(const float aDT) override;
	};
}