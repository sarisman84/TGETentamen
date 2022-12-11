#pragma once
#include "../framework/UICanvas.h"
namespace si 
{
	class InGameHUD : public UICanvas
	{
	public:
		void OnUpdate(const float aDT) override;
	};

}