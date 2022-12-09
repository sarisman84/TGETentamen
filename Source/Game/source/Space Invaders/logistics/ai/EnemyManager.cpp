#include "EnemyManager.h"
#include "../../Entity.h"
#include "../../actors/controllers/EnemyController.h"

#include "../factories/EnemyFactory.h"
#include "../scene management/SceneManager.h"
#include "../../Scene.h"

#include <tge/engine.h>

#include <fstream>
#include <nlohmann/json.hpp>
si::WaveManager::WaveManager()
{
	myCurrentWaveIndex = 0;
	myCanSpawnWavesFlag = false;
}


void si::WaveManager::AddWave(const std::initializer_list<WaveSlot>& someEnemies)
{
	ourInstance->myWaveRegistry.push_back(someEnemies);
}

void si::WaveManager::LoadWaves(const std::string& aPath)
{
	ourInstance->LoadWavesImpl(aPath);
}

void si::WaveManager::LoadWavesImpl(const std::string& aPath)
{
	std::ifstream waveIfs(aPath);

	if (!waveIfs || waveIfs.fail()) return;

	using namespace nlohmann;
	json waveInfo = json::parse(waveIfs);


	for (auto& wave : waveInfo["waves"])
	{
		std::vector<WaveSlot> rWave;
		for (auto& enemy : wave)
		{
			WaveSlot slot;
			slot.myEnemyType = (EnemyID)enemy["type"].get<int>();
			slot.myPosition = Tga::Vector2f(enemy["position"]["x"], enemy["position"]["y"]);
			rWave.push_back(slot);
		}
		myWaveRegistry.push_back(rWave);
	}
}

void si::WaveManager::Update(const float /*aDT*/)
{
	if (!myCanSpawnWavesFlag) return;

	if (IsWaveDead())
	{
		myCurrentWaveIndex++;
		if (myCurrentWaveIndex >= myWaveRegistry.size())
		{
			if (myOnAllWaveClearEvent)
				myOnAllWaveClearEvent();
			//You won
			return;
		}
		SpawnWave();
	}


	UpdateWave();
}

const bool si::WaveManager::IsWaveDead()
{
	return myCurrentWave.empty();
}

void si::WaveManager::MarkAsDead(const uint32_t anEnemyID)
{
	auto& curWave = ourInstance->myCurrentWave;
	curWave.erase(std::remove(curWave.begin(), curWave.end(), anEnemyID), curWave.end());
}

void si::WaveManager::Start()
{
	ourInstance->myCanSpawnWavesFlag = true;
	ourInstance->SpawnWave();
}

void si::WaveManager::Reset()
{
	ourInstance->myCurrentWaveIndex = 0;
}



void si::WaveManager::UpdateWave()
{
	auto scene = SceneManager::GetCurrentScene();
	auto engine = Tga::Engine::GetInstance();
	
	GetFurthestEnemiesOnEdges(scene);

	auto lEntity = (*scene)[myLeftMostEnemy];
	auto rEntity = (*scene)[myRightMostEnemy];

	if (!lEntity || !rEntity) return;

	auto lPos = lEntity->myTransform.Position().x - (lEntity->myTransform.Scale().x / 2.0f);
	auto rPos = rEntity->myTransform.Position().x + (rEntity->myTransform.Scale().x / 2.0f);

	bool isOutOfBoundsL = lPos <= 0;
	bool isOutOfBoundsR = rPos >= engine->GetRenderSize().x;

	if (isOutOfBoundsL || isOutOfBoundsR)
	{
		DecrementPosition();
		//If the group is out of bounds on the left, make the group go to the right
		//If the group is out of bounds on the right, make the group go to the left
		myGroupVelocity = Tga::Vector2f(isOutOfBoundsL ? 1.0f : isOutOfBoundsR ? -1.0f : myGroupVelocity.x, 0.0f);
	}


}

void si::WaveManager::SpawnWave()
{
	auto scene = SceneManager::GetCurrentScene();
	auto& wave = myWaveRegistry[myCurrentWaveIndex];
	for (size_t i = 0; i < wave.size(); i++)
	{
		auto enemy = EnemyFactory::GetEnemy(wave[i].myEnemyType);
		enemy->myTransform.Position() = wave[i].myPosition;
		(*scene) += enemy;

	}
}

void si::WaveManager::DecrementPosition()
{
}

void si::WaveManager::GetFurthestEnemiesOnEdges(Scene* const aScene)
{
	if (!aScene) return;

	float minLeft = FLT_MAX;
	float minRight = 0;
	for (auto& entityID : myCurrentWave)
	{
		auto entity = (*aScene)[entityID];

		if (entity->myTransform.Position().x < minLeft)
		{
			minLeft = entity->myTransform.Position().x;
			myLeftMostEnemy = entityID;
		}

		if (entity->myTransform.Position().x > minRight)
		{
			minRight = entity->myTransform.Position().x;
			myRightMostEnemy = entityID;
		}


	}
}
