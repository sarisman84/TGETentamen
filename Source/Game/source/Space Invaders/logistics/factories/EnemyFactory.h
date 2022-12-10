#pragma once
#include <typeinfo>
#include <type_traits>
#include <unordered_map>

#include <tge/math/Vector.h>
namespace si
{
	class Entity;

	struct EnemyBlueprint
	{
		const wchar_t* myTexture;
		const wchar_t* myBulletTexture;

		float myBulletCollisionRadius;
		float myFireRate;
		float myBulletDamage;
		float myBulletSpeed;
		Tga::Vector2f myBulletFireDir;

		float myHealthAmm = 1;
		float myPointAmm = 10;
	};

	class EnemyFactory
	{
	public:
		EnemyFactory();
	public:

		template<typename Type>
		static void AddType(const Type aKey, const EnemyBlueprint& aNewBlueprint);

		template<typename Type>
		static Entity* const GetEnemy(const Type anEnemyType);
	private:
		void AddType(const uint32_t anID, const EnemyBlueprint& aNewBlueprint);
		Entity* const GetEnemy(const uint32_t anEnemyType);
	private:
		std::unordered_map<uint32_t, EnemyBlueprint> myTypes;

	private:
		inline static EnemyFactory* ourInstance;
	};
	template<typename Type>
	inline void EnemyFactory::AddType(const Type aKey, const EnemyBlueprint& aNewBlueprint)
	{
		static_assert(std::is_enum<Type>::value, "Type is not an Enum");

		uint32_t id = static_cast<uint32_t>(typeid(Type).hash_code());
		uint32_t key = static_cast<uint32_t>(aKey);

		return ourInstance->AddType(id + key, aNewBlueprint);
	}
	template<typename Type>
	inline Entity* const EnemyFactory::GetEnemy(const Type anEnemyType)
	{
		static_assert(std::is_enum<Type>::value, "Type is not an Enum");

		uint32_t id = static_cast<uint32_t>(typeid(Type).hash_code());
		uint32_t key = static_cast<uint32_t>(anEnemyType);

		return ourInstance->GetEnemy(id + key);
	}
}


