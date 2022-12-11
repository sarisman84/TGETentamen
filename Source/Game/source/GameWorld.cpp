#include "stdafx.h"

#include "GameWorld.h"
#include <tge/graphics/GraphicsEngine.h>
#include <tge/drawers/SpriteDrawer.h>
#include <tge/texture/TextureManager.h>
#include <tge/drawers/DebugDrawer.h>

#include "Space Invaders/logistics/ui/CanvasManager.h"
#include "Space Invaders/logistics/ui/canvases/InGameHUD.h"

enum class CanvasTypes
{
	MainMenu, PauseMenu, InGameHUD
};


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
	si::Canvas::ResetTo(CanvasTypes::InGameHUD);

	//Load scene and waves + set some settings
	si::SceneManager::LoadScene("playground.json");
	si::WaveManager::LoadWaves("Data/Waves/testWave.json");
	si::WaveManager::InfiniteWaves() = true;

	//Start the game
	si::WaveManager::Start();
}
void GameWorld::Update(float aTimeDelta)
{
	UNREFERENCED_PARAMETER(aTimeDelta);
	si::SceneManager::Update(aTimeDelta);
	si::WaveManager::Update(aTimeDelta);

	si::Canvas::Update(aTimeDelta);
}

void GameWorld::Render()
{
	si::SceneManager::Render();
	si::Canvas::Render();
}