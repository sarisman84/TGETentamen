#pragma once
#include "../framework/UICanvas.h"
#include <string>

namespace si
{
	class GameOver : public UICanvas
	{
	public:
		GameOver();
		void OnTransitionEnter() override;
		void OnUpdate(const float aDT) override;
	private:
		std::string myInput;
		uint32_t myCurrentEdit;
		std::vector<char> myLetters;
		uint32_t myCurrentLetter;

		bool mySaveFlag;

	private:
		bool myUpInputFlag, myDownInputFlag, myEnterInputFlag;
	};
}