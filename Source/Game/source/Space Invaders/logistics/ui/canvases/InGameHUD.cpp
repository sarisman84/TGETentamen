#include "InGameHUD.h"
#include "../CanvasManager.h"
#include "../../ScoreSystem.h"
#include "../../ai/EnemyManager.h"
#include "../../scene management/SceneManager.h"
#include "../../../Scene.h"
#include "../../../actors/controllers/InputController.h"
void si::InGameHUD::OnUpdate(const float /*aDT*/)
{
	auto scene = SceneManager::GetCurrentScene();
	UI::Begin(this);
	auto viewSize = UI::GetViewSize();
	UI::Text("Score: " + std::to_string(ScoreSystem::GetCurrentScore()), { viewSize.x / 4.0f, viewSize.y - 45.0f });
	UI::Text("Wave: " + std::to_string(WaveManager::GetWaveCount()), { viewSize.x / 2.0f, viewSize.y - 45.0f });

	if (scene)
	{
		auto player = scene->SearchForComponent<InputController>();
		if (player)
		{
			UI::Text("Ammo: " + (player->IsReloading() ? " Reloading " : std::to_string(player->GetCurrentAmmo())), { viewSize.x / 4.0f, 45.0f });
		}

	}

	UI::End();
}
