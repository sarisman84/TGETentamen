#pragma once
#include "Space Invaders/Scene.h"
#include "Space Invaders/logistics/ai/EnemyManager.h"
#include "Space Invaders/logistics/factories/EnemyFactory.h"
#include "Space Invaders/logistics/scene management/SceneManager.h"

class GameWorld
{
public:
	GameWorld();
	~GameWorld();

	void Init();
	void Update(float aTimeDelta);
	void Render();
private: //Space Invaders
	si::SceneManager mySceneManager;
	si::WaveManager myWaveManager;
	si::EnemyFactory myEnemyFactory;
};