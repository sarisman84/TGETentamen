#include "stdafx.h"

#include "GameWorld.h"
#include <tge/graphics/GraphicsEngine.h>
#include <tge/drawers/SpriteDrawer.h>
#include <tge/texture/TextureManager.h>
#include <tge/drawers/DebugDrawer.h>

#include "Space Invaders/logistics/ui/CanvasManager.h"
#include "Space Invaders/logistics/ui/canvases/InGameHUD.h"
#include "Space Invaders/logistics/ui/canvases/GameOver.h"
#include "Space Invaders/logistics/ui/canvases/MainMenu.h"
#include "Space Invaders/logistics/ui/canvases/PauseMenu.h"
#include "Space Invaders/logistics/ui/canvases/CanvasTypes.h"
#include "Space Invaders/logistics/ui/canvases/SaveScore.h"


GameWorld::GameWorld()
{}

GameWorld::~GameWorld()
{}

void GameWorld::Init()
{
	//Initialize ui and canvas systems respectively.
	si::UI::Init();
	si::Canvas::Init();

	si::Canvas::RegisterCanvas(CanvasTypes::InGameHUD, new si::InGameHUD());
	si::Canvas::RegisterCanvas(CanvasTypes::MainMenu, new si::MainMenu());
	si::Canvas::RegisterCanvas(CanvasTypes::PauseMenu, new si::PauseMenu());
	si::Canvas::RegisterCanvas(CanvasTypes::SaveScore, new si::SaveScore());
	si::Canvas::ResetTo(CanvasTypes::MainMenu);

	si::WaveManager::LoadWaves("Data/Waves/testWave.json");

	////Load scene and waves + set some settings
	//si::SceneManager::LoadScene("playground.json");
	//
	//si::WaveManager::InfiniteWaves() = true;

	////Start the game
	//si::WaveManager::Start();
}
void GameWorld::Update(float aTimeDelta)
{
	UNREFERENCED_PARAMETER(aTimeDelta);
	si::SceneManager::Update(aTimeDelta);
	si::WaveManager::Update(aTimeDelta);

	si::Canvas::Update(aTimeDelta);

	if (si::WaveManager::IsGameOver())
	{
		si::WaveManager::Reset();
		si::SceneManager::LoadScene("mainMenu.json");
		si::Canvas::ResetTo(CanvasTypes::GameOver);
	}
}

void GameWorld::Render()
{
	si::SceneManager::Render();
	si::Canvas::Render();
}