#pragma once
#include "../framework/UICanvas.h"
#include <string>
#include <unordered_map>
namespace si
{
	class MainMenu : public UICanvas
	{
		void OnTransitionEnter() override;
		void OnUpdate(const float aDT) override;

	private:
		std::unordered_map<std::string, uint32_t> myData;
	};
}