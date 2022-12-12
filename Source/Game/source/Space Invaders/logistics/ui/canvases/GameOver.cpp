#include "GameOver.h"
#include "../CanvasManager.h"
#include "../../ScoreSystem.h"
#include "../../ai/EnemyManager.h"
#include "../../scene management/SceneManager.h"
#include "../../../Scene.h"
#include "../../../actors/controllers/InputController.h"
#include "../../interaction/HealthInteractor.h"

#include "Space Invaders/logistics/ui/canvases/CanvasTypes.h"


void si::GameOver::OnUpdate(const float /*aDT*/)
{
	auto screenSize = UI::GetViewSize();
	UI::Begin(this);
	auto pos = Tga::Vector2f{ screenSize.x / 2.0f, screenSize.y / 2.0f };
	UI::Text("You died!", pos);
	pos.y -= 50.0f;
	UI::Text("Score: " + std::to_string(ScoreSystem::GetCurrentScore()), pos);
	pos.y -= 50.0f;
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
}
