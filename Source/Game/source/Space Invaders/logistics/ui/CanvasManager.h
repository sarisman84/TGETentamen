#pragma once
#include <vector>
#include <unordered_map>
#include <stack>
#include <memory>
#include <typeinfo>
#include <functional>
#include <tge/math/vector2.h>

namespace si
{
	class UICanvas;

	namespace UI
	{
		uint32_t currentCanvas;
		std::unordered_map<uint32_t, std::shared_ptr<UICanvas>> canvases;
		std::stack<uint32_t> updateStack;
		std::stack<uint32_t> renderStack;

		template<typename CanvasKey, typename Type>
		void RegisterCanvas(const CanvasKey aKey);
		void RegisterCanvas(const uint32_t anID, UICanvas* aCanvas);

		template<typename CanvasKey>
		void TransitionToCanvas(const CanvasKey aKey, const bool anUpdatePreviousCanvas = false, const bool aRenderPreviousCanvas = false);
		void TransitionToCanvas(const uint32_t anID, const bool anUpdatePreviousCanvas, const bool aRenderPreviousCanvas);

		void TransitionBack();

		template<typename CanvasKey>
		void ResetToCanvas(const CanvasKey aKey);
		void ResetToCanvas(const uint32_t anID);


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
		void TransitionToCanvas(const CanvasKey aKey, const bool anUpdatePreviousCanvas, const bool aRenderPreviousCanvas)
		{
			uint32_t id = static_cast<uint32_t>(typeid(CanvasKey).hash_code());
			uint32_t key = static_cast<uint32_t>(aKey);
			UI::TransitionTo(id + key, anUpdatePreviousCanvas, aRenderPreviousCanvas);
		}

		template<typename CanvasKey>
		void ResetToCanvas(const CanvasKey aKey)
		{
			static_assert(std::is_enum<CanvasKey>::value, "Test");

			uint32_t id = static_cast<uint32_t>(typeid(CanvasKey).hash_code());
			uint32_t key = static_cast<uint32_t>(aKey);
			UI::ResetToCanvas(id + key);
		}


		void Begin(UICanvas* const aCanvas);
		void End();
		void Text(const std::string& someText, Tga::Vector2f aPosition);
		void Button(const std::string& someText, Tga::Vector2f aPosition, std::function<void()> aCallback);

		Tga::Vector2f GetViewSize();


	}



}


