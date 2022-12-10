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
	si::SceneManager::LoadScene("playground.json");
	si::WaveManager::LoadWaves("Data/Waves/testWave.json");
	si::WaveManager::Start();
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