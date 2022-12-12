#pragma once
#include "../../Component.h"


#include <functional>

namespace si
{
	enum class Layer : uint32_t
	{
		Everything = 1,
		Player = 2,
		Enemy = 4,
		Bullet = 8,
		Shelter = 16
	};


	class Collider : public Component
	{
	public: //Core
		void Awake() override;
		void Update(const float aDT) override;
		void OnDestroy() override;
	public: //Collision Logic
		const bool TriggerCollisionEvent(Entity* const someOtherEntity);
		const bool HasCollidedWith(Collider* const someOtherCollider);
		const bool HasCollisionEventTriggered();
	public: //Accessors
		inline Entity* const GetEntity() const { return myEntity; }
		inline std::function<void(Entity*)>& OnCollisionEvent() { return myOnCollisionEnterEvent; }
		inline void SetLayer(const unsigned char someLayers) { myCollisionLayer = someLayers; }

		template<typename... Enum>
		inline void SetLayer(const Enum&&... someLayers) 
		{
			static_assert(std::is_enum<Enum>::value, "Corresponding type is not an enum!");

			unsigned char result;

			(result |= static_cast<unsigned char>(...) | someLayers);


			SetLayer(result);
		}
	public:
		float myCollisionRadius = 10.0f;
		unsigned char myCollisionLayer = (unsigned char)Layer::Everything;
	private:
		std::function<void(Entity*)> myOnCollisionEnterEvent;
		bool myCollisionState = false;


	};
}