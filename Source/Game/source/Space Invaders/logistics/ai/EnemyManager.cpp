#include "EnemyManager.h"
#include "../../Entity.h"
#include "../../actors/controllers/EnemyController.h"
#include "../../actors/8BitActor.h"

#include "../factories/EnemyFactory.h"
#include "../scene management/SceneManager.h"
#include "../../Scene.h"
#include "../logging/Logger.h"

#include <tge/engine.h>
#include <tge/settings/settings.h>

#include <fstream>
#include <nlohmann/json.hpp>


si::WaveManager::WaveManager()
{
	myCurrentWaveIndex = 0;
	myCanSpawnWavesFlag = false;
	ourInstance = this;
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
	std::ifstream waveIfs(Tga::Settings::GetAssetW(aPath));

	if (!waveIfs || waveIfs.fail())
	{
		ERROR_LOG("Could not load wave from (" + aPath + ") [File not found]");
		return;
	}
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
	if (!ourInstance) return;
	if (!ourInstance->myCanSpawnWavesFlag) return;

	if (ourInstance->IsWaveDead())
	{
		ourInstance->myCurrentWaveIndex++;
		if (ourInstance->myCurrentWaveIndex >= ourInstance->myWaveRegistry.size())
		{
			if (ourInstance->myOnAllWaveClearEvent)
				ourInstance->myOnAllWaveClearEvent();

			ourInstance->myCanSpawnWavesFlag = false;
			LOG("All Waves cleared!");
			//You won
			return;
		}
		ourInstance->SpawnWave();
	}


	ourInstance->UpdateWave();
}

const bool si::WaveManager::IsWaveDead()
{
	bool isWaveDead = myCurrentWave.empty();
	if (isWaveDead)
		LOG("Current wave has no remaining enemies alive!");
	return isWaveDead;
}

void si::WaveManager::MarkAsDead(const uint32_t anEnemyID)
{
	auto& curWave = ourInstance->myCurrentWave;
	curWave.erase(std::remove(curWave.begin(), curWave.end(), anEnemyID), curWave.end());
	LOG("Entity " + std::to_string(anEnemyID) + " is dead. Clearing wave cache!");
	LOG("Current Wave: [" + std::to_string(ourInstance->myCurrentWave.size()) + " remaining]");
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

	auto lActor = lEntity->GetComponent<EightBitActor>();
	auto rActor = rEntity->GetComponent<EightBitActor>();

	if (!lActor || !rActor) return;

	auto lPos = lActor->GetNextPosition().x - (lEntity->mySprite.mySize.x / 2.0f);
	auto rPos = rActor->GetNextPosition().x + (rEntity->mySprite.mySize.x / 2.0f);

	bool isOutOfBoundsL = lPos <= 0;
	bool isOutOfBoundsR = rPos >= engine->GetRenderSize().x;

	if (isOutOfBoundsL || isOutOfBoundsR)
	{
		myGroupReachedEdgeFlag = true;
		//If the group is out of bounds on the left, make the group go to the right
		//If the group is out of bounds on the right, make the group go to the left
		myGroupVelocity = Tga::Vector2f(isOutOfBoundsL ? 1.0f : isOutOfBoundsR ? -1.0f : myGroupVelocity.x, 0.0f);
	}


}

void si::WaveManager::SpawnWave()
{
	myGroupVelocity = { 1.0f, 0.0f };
	LOG("Initializing Wave " + std::to_string(myCurrentWaveIndex));
	LOG("Initial Group Velocity [" + std::to_string(myGroupVelocity.x) + ", " + std::to_string(myGroupVelocity.y) + "]");
	auto scene = SceneManager::GetCurrentScene();
	auto& wave = myWaveRegistry[myCurrentWaveIndex];
	for (size_t i = 0; i < wave.size(); i++)
	{
		auto enemy = EnemyFactory::GetEnemy(wave[i].myEnemyType);
		enemy->myTransform.Position() = wave[i].myPosition;
		(*scene) += enemy;
		LOG("Spawned Enemy [" + std::to_string(static_cast<int>(wave[i].myEnemyType)) + "] at " + std::to_string(wave[i].myPosition.x) + ", " + std::to_string(wave[i].myPosition.y));
		myCurrentWave.push_back(enemy->GetUUID());
	}
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
