#include "InGameHUD.h"
#include "../CanvasManager.h"
#include "../../ScoreSystem.h"
#include "../../ai/EnemyManager.h"
#include "../../scene management/SceneManager.h"
#include "../../../Scene.h"
#include "../../../actors/controllers/InputController.h"
#include "../../interaction/HealthInteractor.h"

#include "Space Invaders/logistics/ui/canvases/CanvasTypes.h"
void si::InGameHUD::OnTransitionEnter()
{
	myCurDelay = myDelay;
}
void si::InGameHUD::OnUpdate(const float aDT)
{

	constexpr unsigned char escapeBind = 0x50; //P
	auto scene = SceneManager::GetCurrentScene();
	if (scene->Contains<InputController>())
	{
		auto player = scene->SearchForComponent<InputController>();


		UI::Begin(this);
		auto viewSize = UI::GetViewSize();
		UI::Text("Score: " + std::to_string(ScoreSystem::GetCurrentScore()), { viewSize.x / 4.0f, viewSize.y - 45.0f });
		UI::Text("Wave: " + std::to_string(WaveManager::GetWaveCount()), { viewSize.x / 2.0f, viewSize.y - 45.0f });

		if (scene)
		{
			auto health = player->GetEntity()->GetComponent<HealthInteractor>();
			UI::Text("Health: " + std::to_string(static_cast<int>(health->GetCurrentHealth())), { viewSize.x - (viewSize.x / 4.0f) ,viewSize.y - 45.0f });
			UI::Text("Ammo: " + (player->IsReloading() ? " Reloading " : std::to_string(player->GetCurrentAmmo())), { viewSize.x / 4.0f, 45.0f });
		}

		UI::End();
	}


	myCurDelay -= aDT;
	if (myCurDelay > 0) return;

	if (GetAsyncKeyState(escapeBind))
	{
		Canvas::TransitionTo(CanvasTypes::PauseMenu);
		scene->SetUpdateActive(false);
	}
}
