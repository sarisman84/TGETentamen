#pragma once
#include "../ui/framework/UIContent.h"

#include <unordered_map>
#include <functional>

namespace si
{
	class UICanvas;

	struct UIContentBlueprint 
	{
		std::function<void(UIContent*)> myCreationEvent;
		std::function<void(UICanvas*, UIContent*)> myRenderEvent;
	};

	class UIFactory
	{
	public:
		UIFactory();
	public:
		template<typename Key>
		static UIContent* GetElement(const Key aKey);
		template<typename Key>
		static void AddType(const Key aKey, const UIContentBlueprint& anOnRenderCallback);
	private:
		UIContent* GetElement(const uint32_t anID);
		void AddType(const uint32_t anID, const UIContentBlueprint& anOnRenderCallback);
	private:
		std::unordered_map<uint32_t, UIContentBlueprint> myUITypes;
	private:
		inline static UIFactory* ourInstance;
	};

	template<typename Key>
	inline UIContent* UIFactory::GetElement(const Key aKey)
	{
		uint32_t id = static_cast<uint32_t>(typeid(Key).hash_code());
		uint32_t key = static_cast<uint32_t>(aKey);

		return GetElement(id + key);
	}
	template<typename Key>
	inline void UIFactory::AddType(const Key aKey, const UIContentBlueprint& aContentBlueprint)
	{
		uint32_t id = static_cast<uint32_t>(typeid(Key).hash_code());
		uint32_t key = static_cast<uint32_t>(aKey);

		return AddType(id + key, anOnRenderCallback);
	}
}