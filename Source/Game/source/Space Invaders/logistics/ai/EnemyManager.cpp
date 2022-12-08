#include "EnemyManager.h"

si::WaveManager::WaveManager() = default;

si::WaveManager::WaveManager(Scene* const aScene) : myCurrentScene(aScene)
{
	myCurrentWaveIndex = 0;
}

void si::WaveManager::AddWave(const std::initializer_list<Enemy>& someEnemies)
{
	myWaveRegistry.push_back(someEnemies);
}

void si::WaveManager::Update(const float aDT)
{
	if (IsWaveDead())
	{
		SpawnWave();
	}


	UpdateWave();
}

const bool si::WaveManager::IsWaveDead()
{
	return myCurrentWave.empty();
}

void si::WaveManager::UpdateWave()
{
	
}

void si::WaveManager::SpawnWave()
{
	auto& wave = myWaveRegistry[myCurrentWaveIndex];
	for (size_t i = 0; i < wave.size(); i++)
	{
		auto& enemy = wave[i];
	}
}

void si::WaveManager::DecrementPosition()
{
}
