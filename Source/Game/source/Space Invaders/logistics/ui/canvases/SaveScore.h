#pragma once
#include "Space Invaders/logistics/ui/framework/UICanvas.h"

#include <tge/math/Vector.h>

#include <string>
#include <array>
#include <unordered_map>
namespace si 
{
	class SaveScore : public UICanvas
	{
	public:
		SaveScore();
	private:
		void ResetInput();
		void Apply();
		void IncrementInput();
		void DecrementInput();
	private:
		void DisplayCurrentScore(Tga::Vector2f aPos);
		void DisplayHighscores(Tga::Vector2f aPos);
		void DisplayCurrentInput(Tga::Vector2f aPos);
	public:
		void OnTransitionEnter() override;
		void OnUpdate(const float aDT);
	private:
		const uint8_t myMaxNameLength = 3;
		const float myInputDelay = 0.15f;
	private:
		float myCurrentDelay = 0;
		uint8_t myInputIndex = 0;
		uint8_t myCurrentLetter = 0;
		std::string myInput = "___";
	private:
		std::array<char, 25> myLetters;
		std::unordered_map<std::string, uint32_t> myData;
	};
}


