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
}

void si::MainMenu::OnUpdate(const float /*aDT*/)
{
	UI::Begin(this);
	auto screenSize = UI::GetViewSize();
	auto pos = Tga::Vector2f(screenSize.x / 2.0f, screenSize.y / 2.0f);
	UI::Text("Space Invaders", pos);
	pos.y -= 100.0f;
	UI::Text("Press Space to Start", pos);
	UI::End();

	if (GetAsyncKeyState(VK_SPACE))
	{
		SceneManager::LoadScene("playground.json", true);
		WaveManager::InfiniteWaves() = true;
		WaveManager::Start();
		Canvas::ResetTo(CanvasTypes::InGameHUD);
	}
}
