#pragma once
#include "../framework/UICanvas.h"
namespace si
{
	class GameOver : public UICanvas
	{
		void OnUpdate(const float aDT) override;
	};
}