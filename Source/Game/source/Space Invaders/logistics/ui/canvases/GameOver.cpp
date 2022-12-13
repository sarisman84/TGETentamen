#include "GameOver.h"
#include "../CanvasManager.h"
#include "../../ScoreSystem.h"
#include "../../ai/EnemyManager.h"
#include "../../scene management/SceneManager.h"
#include "../../../Scene.h"
#include "../../../actors/controllers/InputController.h"
#include "../../interaction/HealthInteractor.h"

#include "Space Invaders/logistics/ui/canvases/CanvasTypes.h"


si::GameOver::GameOver()
{
	myLetters.push_back('A');
	myLetters.push_back('B');
	myLetters.push_back('C');
	myLetters.push_back('D');
	myLetters.push_back('E');
	myLetters.push_back('F');
	myLetters.push_back('G');
	myLetters.push_back('H');
	myLetters.push_back('I');
	myLetters.push_back('J');
	myLetters.push_back('K');
	myLetters.push_back('L');
	myLetters.push_back('O');
	myLetters.push_back('P');
	myLetters.push_back('S');
	myLetters.push_back('W');
	myLetters.push_back('V');
	myLetters.push_back('Q');
	myLetters.push_back('R');
	myLetters.push_back('T');
	myLetters.push_back('U');
	myLetters.push_back('M');
	myLetters.push_back('N');
	myLetters.push_back('Z');
	myLetters.push_back('X');

}

void si::GameOver::OnTransitionEnter()
{
	myCurrentLetter = 0;
	myCurrentEdit = 0;
	myInput = "___";
	mySaveFlag = false;
}

void si::GameOver::OnUpdate(const float /*aDT*/)
{
	auto screenSize = UI::GetViewSize();
	UI::Begin(this);
	auto pos = Tga::Vector2f{ screenSize.x / 2.0f, screenSize.y / 2.0f };
	UI::Text("You died!", pos);
	pos.y -= 50.0f;
	UI::Text("Score: " + std::to_string(ScoreSystem::GetCurrentScore()), pos);
	pos.y -= 50.0f;
	UI::Text(mySaveFlag ? "Saved!" : "Name: " + myInput, pos);
	pos.y -= 150.0f;
	pos.x -= 150.0f;
	UI::Text("Try Again [Space]", pos);
	pos.x += 300.0f;
	UI::Text("Leave [Escape]", pos);
	UI::End();


	if (GetAsyncKeyState(VK_SPACE))
	{
		SceneManager::LoadScene("playground.json", true);
		Canvas::ResetTo(CanvasTypes::InGameHUD);
		WaveManager::Start();
	}

	if (GetAsyncKeyState(VK_ESCAPE))
	{
		Canvas::ResetTo(CanvasTypes::MainMenu);
		SceneManager::LoadScene("mainMenu.json");
	}

	if (mySaveFlag) return;
	if (!myEnterInputFlag) {
		if (GetAsyncKeyState(VK_RETURN))
		{
			if (myCurrentEdit >= myInput.size())
			{
				ScoreSystem::SaveScore(myInput);
				mySaveFlag = true;
			}

			myCurrentEdit++;
			myEnterInputFlag = true;
		}
	}
	else {
		myEnterInputFlag = false;
	}


	if (!myUpInputFlag)
	{
		if (GetAsyncKeyState(VK_UP))
		{
			myCurrentLetter++;

			if (myCurrentLetter >= myLetters.size())
				myCurrentLetter = 0;
			myInput[myCurrentEdit] = myLetters[myCurrentLetter];
			myUpInputFlag = true;
		}
	}

	else
	{
		myUpInputFlag = false;
	}

	if (!myDownInputFlag) {
		if (GetAsyncKeyState(VK_DOWN))
		{
			myCurrentLetter--;
			myInput[myCurrentEdit] = myLetters[myCurrentLetter];
			if (myCurrentLetter <= 0)
				myCurrentLetter = static_cast<uint32_t>(myLetters.size());
			myInput[myCurrentEdit] = myLetters[myCurrentLetter];

			myDownInputFlag = true;
		}
	}

	else
	{
		myDownInputFlag = false;
	}

}
