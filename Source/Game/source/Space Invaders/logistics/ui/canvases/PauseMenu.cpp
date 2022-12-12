#include "PauseMenu.h"

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

void si::PauseMenu::OnTransitionEnter()
{
	myCurDelay = myDelay;
	myInputDelayTrigger = false;
}

void si::PauseMenu::OnUpdate(const float aDT)
{
	auto scene = SceneManager::GetCurrentScene();
	constexpr unsigned char resumeBind = 0x50; //P
	UI::Begin(this);

	auto size = UI::GetViewSize();
	auto pos = Tga::Vector2f{ size.x / 2.0f,(size.y / 2.0f) + 50.0f };

	UI::Text("Paused", pos);
	pos.y -= 50.0f;
	pos.x -= 150.0f;
	UI::Text("Resume [P]", pos);
	pos.x += 250.0f;
	UI::Text("Leave [Escape]", pos);
	UI::End();

	myCurDelay -= aDT;
	if (myCurDelay > 0) return;

	if (GetAsyncKeyState(resumeBind) && myInputDelayTrigger)
	{
		Canvas::TransitionBack();
		scene->SetUpdateActive(true);
		myInputDelayTrigger = true;
	}
	if (GetAsyncKeyState(VK_ESCAPE) && !myInputDelayTrigger)
	{
		scene->SetUpdateActive(true);
		WaveManager::Reset();
		Canvas::ResetTo(CanvasTypes::MainMenu);
		myInputDelayTrigger = true;
	}
}
