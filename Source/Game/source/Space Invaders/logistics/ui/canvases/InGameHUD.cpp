#include "InGameHUD.h"
#include "../CanvasManager.h"
#include "../../ScoreSystem.h"
void si::InGameHUD::OnInit()
{
	UI::Begin(this);
	auto viewSize = UI::GetViewSize();
	UI::Text("Score: " + std::to_string(ScoreSystem::GetCurrentScore()), { viewSize.x / 4.0f, viewSize.y - 45.0f});
	UI::End();
}
