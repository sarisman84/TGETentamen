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


	public: //Getters and Setters
		static inline bool& InfiniteWaves() { return ourInstance->myInfiniteWavesFlag; }
		static inline const Tga::Vector2f GetGroupVelocity()
		{
			if (ourInstance->myGroupReachedEdgeFlag)
			{
				return Tga::Vector2f(0.0f, -1.0f);
			}
			return ourInstance->myGroupVelocity;
		}
		static inline void ResetDecentFlag() { ourInstance->myGroupReachedEdgeFlag = false; }
		static inline std::function<void()>& OnAllWavesCleared() { return ourInstance->myOnAllWaveClearEvent; }
		static inline const uint32_t GetWaveCount() { return ourInstance->myWaveCount; }
		const bool IsWaveDead();
	public: //Communicators
		static void AddWave(const std::initializer_list<WaveSlot>& someEnemies);
		static void LoadWaves(const std::string& aPath);
		static void MarkAsDead(const uint32_t anEnemyID);
		static void Start();
		static void Reset();
		static void Update(const float aDT);
	private:
		void LoadWavesImpl(const std::string& aPath);
		void UpdateWave();
		void SpawnWave();
	private:
		void GetFurthestEnemiesOnEdges(Scene* const aScene);

	private:
		std::vector<uint32_t> myCurrentWave;
		std::vector<std::vector<WaveSlot>> myWaveRegistry;
		std::function<void()> myOnAllWaveClearEvent;
	private: //Data
		Tga::Vector2f myGroupVelocity;
		bool myCanSpawnWavesFlag;
		bool myInfiniteWavesFlag;
		bool myGroupReachedEdgeFlag;
		uint32_t myCurrentWaveIndex;
		uint32_t
			myLeftMostEnemy,
			myRightMostEnemy;
		uint32_t myWaveCount;
	private:
		inline static WaveManager* ourInstance;
	};
}