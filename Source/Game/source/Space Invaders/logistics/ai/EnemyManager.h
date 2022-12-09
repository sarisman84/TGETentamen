#pragma once
#include <vector>
#include <functional>

#include <tge/math/vector2.h>
#include "../../enemy/EnemyInfo.h"

namespace si
{


	class Entity;
	class Scene;

	struct WaveSlot
	{
		EnemyID myEnemyType;
		Tga::Vector2f myPosition;
	};

	class WaveManager
	{
	public:
		WaveManager();
	public:

		void Update(const float aDT);
	public: //Getters and Setters
		static inline const Tga::Vector2f GetGroupVelocity() { return ourInstance->myGroupVelocity; }
		static inline std::function<void()>& OnAllWavesCleared() { return ourInstance->myOnAllWaveClearEvent; }
		const bool IsWaveDead();
	public: //Communicators
		static void AddWave(const std::initializer_list<WaveSlot>& someEnemies);
		static void LoadWaves(const std::string& aPath);
		static void MarkAsDead(const uint32_t anEnemyID);
		static void Start();
		static void Reset();

	private:
		void LoadWavesImpl(const std::string& aPath);

		void UpdateWave();
		void SpawnWave();
		void DecrementPosition();

	private:
		void GetFurthestEnemiesOnEdges(Scene* const aScene);

	private:
		std::vector<uint32_t> myCurrentWave;
		std::vector<std::vector<WaveSlot>> myWaveRegistry;
		std::function<void()> myOnAllWaveClearEvent;
	private:
		Tga::Vector2f myGroupVelocity;
		bool myCanSpawnWavesFlag;
		uint32_t myCurrentWaveIndex;
		uint32_t
			myLeftMostEnemy,
			myRightMostEnemy;
	private:
		inline static WaveManager* ourInstance;
	};
}