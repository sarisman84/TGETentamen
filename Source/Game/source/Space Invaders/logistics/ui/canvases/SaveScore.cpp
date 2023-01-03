#include "SaveScore.h"
#include "Space Invaders/logistics/ui/CanvasManager.h"
#include "Space Invaders/logistics/scene management/SceneManager.h"
#include "Space Invaders/logistics/ui/canvases/CanvasTypes.h"
#include "Space Invaders/logistics/ai/EnemyManager.h"
#include "Space Invaders/logistics/ScoreSystem.h"

#include <wtypes.h>

si::SaveScore::SaveScore()
{
	myLetters[0] = 'A';
	myLetters[1] = 'B';
	myLetters[2] = 'C';
	myLetters[3] = 'D';
	myLetters[4] = 'E';
	myLetters[5] = 'F';
	myLetters[6] = 'G';
	myLetters[7] = 'H';
	myLetters[8] = 'I';
	myLetters[9] = 'J';
	myLetters[10] = 'K';
	myLetters[11] = 'L';
	myLetters[12] = 'O';
	myLetters[13] = 'P';
	myLetters[14] = 'S';
	myLetters[15] = 'W';
	myLetters[16] = 'V';
	myLetters[17] = 'Q';
	myLetters[18] = 'R';
	myLetters[19] = 'T';
	myLetters[20] = 'U';
	myLetters[21] = 'M';
	myLetters[22] = 'N';
	myLetters[23] = 'Z';
	myLetters[24] = 'X';
}

void si::SaveScore::ResetInput()
{
	myInput = "___";
	myCurrentLetter = 0;
	myInputIndex = 0;
	myCurrentDelay = 0;

}

void si::SaveScore::Apply()
{
	if (myCurrentDelay < myInputDelay) return;
	if (myInputIndex >= myMaxNameLength)
	{
		//go to whatever canvas it should go.
		Canvas::TransitionBack();
		return;
	}
	auto i = myInputIndex++;
	myInput[i] = myLetters[myCurrentLetter];
	myCurrentDelay = 0;

	if (i == myMaxNameLength - 1)
		ScoreSystem::SaveScore(myInput);
}

void si::SaveScore::IncrementInput()
{
	if (myCurrentDelay < myInputDelay) return;
	myCurrentLetter++;
	if (myCurrentLetter >= myLetters.size())
		myCurrentLetter = 0;
	myCurrentDelay = 0;
}

void si::SaveScore::DecrementInput()
{
	if (myCurrentDelay < myInputDelay) return;
	myCurrentLetter--;
	if (myCurrentLetter == UINT8_MAX)
		myCurrentLetter = static_cast<uint8_t>(myLetters.size()) - 1;
	myCurrentDelay = 0;
}

void si::SaveScore::DisplayCurrentScore(Tga::Vector2f aPos)
{
	auto title = aPos + Tga::Vector2f(0, 50.0f);
	UI::Text("Final Score", title);
	UI::Text(std::to_string(ScoreSystem::GetCurrentScore()), aPos);
}

void si::SaveScore::DisplayHighscores(Tga::Vector2f aPos)
{
	auto title = aPos + Tga::Vector2f(0, 100.0f);

	UI::Text("---Highscore---", title);
	auto scorePos = aPos;
	for (auto& score : myData)
	{
		UI::Text(score.first + " - " + std::to_string(score.second), scorePos);
		scorePos.y -= 50.0f;
	}

}

void si::SaveScore::DisplayCurrentInput(Tga::Vector2f aPos)
{
	std::string result;
	for (size_t i = 0; i < myInput.size(); i++)
	{
		if (i == myInputIndex) {
			result.push_back('[');
			result.push_back(myLetters[myCurrentLetter]);
			result.push_back(']');
		}
		else
		{
			result.push_back(myInput[i]);
		}

	}
	UI::Text(result, aPos);
}

void si::SaveScore::OnTransitionEnter()
{
	ResetInput();
	myData = ScoreSystem::LoadHighScores();
}

void si::SaveScore::OnUpdate(const float aDT)
{
	myCurrentDelay += aDT;
	UI::Begin(this);
	auto screenSize = UI::GetViewSize();
	Tga::Vector2f center = { screenSize.x / 2.0f, screenSize.y / 2.0f };
	DisplayCurrentScore(Tga::Vector2f(center.x - 150.0f, center.y + 100.0f));
	DisplayHighscores(Tga::Vector2f(center.x + 150.0f, center.y + 50.0f));
	if (ScoreSystem::GetCurrentScore() > 0)
		DisplayCurrentInput(Tga::Vector2f(center.x, center.y - 250.0f));
	auto descPos = Tga::Vector2f(center.x - 175.0f, center.y - 300.0f);

	if (myInputIndex < myMaxNameLength && ScoreSystem::GetCurrentScore() > 0)
	{
		UI::Text("[Up Arrow]/[Down Arrow] select letter", descPos);
		descPos.y -= 25.0f;
		UI::Text("[Enter] Apply", descPos);
		descPos.x += 150.0f;
		UI::Text("[Escape] Exit", descPos);
	}
	else
		UI::Text("[Enter or Escape] Exit", descPos);

	UI::End();


	if (ScoreSystem::GetCurrentScore() > 0)
	{
		if (GetAsyncKeyState(VK_UP))
		{
			IncrementInput();
		}
		else if (GetAsyncKeyState(VK_DOWN))
		{
			DecrementInput();
		}

		if (GetAsyncKeyState(VK_RETURN))
		{
			Apply();
		}
	}


	if (GetAsyncKeyState(VK_ESCAPE) && myCurrentDelay >= myInputDelay)
	{
		Canvas::TransitionBack();
		myCurrentDelay = 0;
	}
}
