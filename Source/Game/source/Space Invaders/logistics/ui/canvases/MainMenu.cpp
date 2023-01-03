#include "MainMenu.h"
#include "../CanvasManager.h"
#include "../../ScoreSystem.h"
#include "../../ai/EnemyManager.h"
#include "../../scene management/SceneManager.h"
#include "../../../Scene.h"
#include "../../../actors/controllers/InputController.h"
#include "../../interaction/HealthInteractor.h"

#include "Space Invaders/logistics/scene management/SceneManager.h"
#include "Space Invaders/logistics/ai/EnemyManager.h"
#include "Space Invaders/logistics/ui/canvases/CanvasTypes.h"

void si::MainMenu::OnTransitionEnter()
{
	SceneManager::LoadScene("mainMenu.json");
	myData = ScoreSystem::LoadHighScores();
}

void si::MainMenu::OnUpdate(const float /*aDT*/)
{

	UI::Begin(this);
	auto screenSize = UI::GetViewSize();

	const Tga::Vector2f center = { screenSize.x / 2.0f, screenSize.y / 2.0f };

	auto highscorePos = center;
	auto titlePos = center;
	auto authorPos = center - Tga::Vector2f{ 475.0f, 475.0f };
	titlePos.x -= 150.0f;
	UI::Text("Spyro's Space Invaders", titlePos, 1.5f);

	auto enterDialogPos = titlePos;
	enterDialogPos.y -= 200.0f;
	enterDialogPos.x += 10.0f;
	UI::Text("Press Space to Start", enterDialogPos);


	highscorePos.x += 350.0f;
	UI::Text("---Highscores--", highscorePos);
	highscorePos.y -= 75.0f;
	for (auto& d : myData)
	{
		UI::Text(d.first + " - " + std::to_string(d.second), highscorePos);
		highscorePos.y -= 50.0f;
	}


	UI::Text("Made by Spyridon Passas (SP21)", authorPos);

	UI::End();

	if (GetAsyncKeyState(VK_SPACE))
	{
		SceneManager::LoadScene("playground.json", true);
		WaveManager::InfiniteWaves() = true;
		WaveManager::Start();
		Canvas::ResetTo(CanvasTypes::InGameHUD);
	}
}
