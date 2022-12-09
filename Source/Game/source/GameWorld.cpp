#include "stdafx.h"

#include "GameWorld.h"
#include <tge/graphics/GraphicsEngine.h>
#include <tge/drawers/SpriteDrawer.h>
#include <tge/texture/TextureManager.h>
#include <tge/drawers/DebugDrawer.h>




GameWorld::GameWorld()
{}

GameWorld::~GameWorld()
{}

void GameWorld::Init()
{
	si::SceneManager::LoadScene("mainMenu.json");
	si::WaveManager::LoadWaves("Data/Waves/testWave.json");
}
void GameWorld::Update(float aTimeDelta)
{
	UNREFERENCED_PARAMETER(aTimeDelta);
	si::SceneManager::Update(aTimeDelta);
}

void GameWorld::Render()
{
	si::SceneManager::Render();
}