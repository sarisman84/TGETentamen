#pragma once
#include <vector>

#include <tge/math/vector2.h>

namespace si
{
	class Scene;
	struct Enemy
	{
		enum class Type
		{
			Default,
			Tier1,
			Tier2
		};

		Type myEnemyType;
	};


	class WaveManager
	{
	public:
		WaveManager();
		WaveManager(Scene* const aScene);
	public:
		void AddWave(const std::initializer_list<Enemy>& someEnemies);
		void Update(const float aDT);
	public:
		inline const Tga::Vector2f GetGroupVelocity() { return myGroupVelocity; }
		const bool IsWaveDead();
	private:
		void UpdateWave();
		void SpawnWave();
		void DecrementPosition();

	private:
		std::vector<uint32_t> myCurrentWave;
		std::vector<std::vector<Enemy>> myWaveRegistry;
		uint32_t myCurrentWaveIndex;
	private:
		Tga::Vector2f myGroupVelocity;
	private:
		Scene* myCurrentScene;
	};
}