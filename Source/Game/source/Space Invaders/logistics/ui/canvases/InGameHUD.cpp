#include "InGameHUD.h"
#include "../CanvasManager.h"
#include "../../ScoreSystem.h"
#include "../../ai/EnemyManager.h"
void si::InGameHUD::OnUpdate(const float /*aDT*/)
{
	UI::Begin(this);
	auto viewSize = UI::GetViewSize();
	UI::Text("Score: " + std::to_string(ScoreSystem::GetCurrentScore()), { viewSize.x / 4.0f, viewSize.y - 45.0f });
	UI::Text("Wave: " + std::to_string(WaveManager::GetWaveCount()), { viewSize.x / 2.0f, viewSize.y - 45.0f });
	UI::End();
}
