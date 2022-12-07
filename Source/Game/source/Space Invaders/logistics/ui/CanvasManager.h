#pragma once
#include <vector>
#include <unordered_map>
#include <stack>
#include <memory>
#include <typeinfo>

namespace si
{
	class UICanvas;


	std::unordered_map<uint32_t, std::shared_ptr<UICanvas>> canvases;
	std::stack<uint32_t> updateStack;
	std::stack<uint32_t> renderStack;

	template<typename CanvasKey, typename Type>
	void RegisterCanvas(const CanvasKey aKey);
	void RegisterCanvas(const uint32_t anID, UICanvas* aCanvas);

	template<typename CanvasKey>
	void TransitionTo(const CanvasKey aKey, const bool anUpdatePreviousCanvas = false, const bool aRenderPreviousCanvas = false);
	void TransitionTo(const uint32_t anID, const bool anUpdatePreviousCanvas, const bool aRenderPreviousCanvas);

	void TransitionBack();

	template<typename CanvasKey>
	void ResetTo(const CanvasKey aKey);
	void ResetTo(const uint32_t anID);


	void UpdateCanvasStack(const float aDT);
	void RenderCanvasStack();


	template<typename CanvasKey, typename Type>
	void RegisterCanvas(const CanvasKey aKey)
	{
		uint32_t id = static_cast<uint32_t>(typeid(CanvasKey).hash_code());
		uint32_t key = static_cast<uint32_t>(aKey);
		si::RegisterCanvas(id + key, new Type());
	}

	template<typename CanvasKey>
	void TransitionTo(const CanvasKey aKey, const bool anUpdatePreviousCanvas, const bool aRenderPreviousCanvas)
	{
		uint32_t id = static_cast<uint32_t>(typeid(CanvasKey).hash_code());
		uint32_t key = static_cast<uint32_t>(aKey);
		si::TransitionTo(id + key, anUpdatePreviousCanvas, aRenderPreviousCanvas);
	}

	template<typename CanvasKey>
	void ResetTo(const CanvasKey aKey)
	{
		static_assert(std::is_enum<CanvasKey>::value, "Test");

		uint32_t id = static_cast<uint32_t>(typeid(CanvasKey).hash_code());
		uint32_t key = static_cast<uint32_t>(aKey);
		si::ResetTo(id + key);
	}

}


