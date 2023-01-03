#pragma once
#include <vector>
#include <unordered_map>
#include <stack>
#include <memory>
#include <typeinfo>
#include <functional>
#include <tge/math/vector2.h>
#include <tge/math/color.h>

#include "Space Invaders/logistics/ui/framework/UICanvas.h"

namespace si
{
	class UIContent;



	namespace Canvas
	{
		class CanvasContext
		{
		public: //Logistics
			friend void Update(const float aDT);
			friend void Render();
		public: //Core Accessors/tools for Canvases
			friend void RegisterCanvas(const uint32_t anID, UICanvas* const aCanvas);
			friend void TransitionTo(const uint32_t anID, const bool aKeepUpdatingPreviousCanvas = false, const bool aKeepRenderingPreviousCanvas = false);
			friend void TransitionBack();
			friend void ResetTo(const uint32_t anID);
		private:
			template<typename Key>
			friend uint32_t CalculateKey(const Key aKey);
		private:
			std::stack<std::tuple<uint32_t, bool>> myCanvasStack;
			std::stack<std::tuple<uint32_t, bool>> myRenderStack;
			std::unordered_map<uint32_t, std::unique_ptr<UICanvas>> myCanvases;
		};
		inline CanvasContext canvasContext;

		void Init();

		template<typename Type, typename TCanvas>
		void RegisterCanvas(const Type aType, TCanvas* const aCanvas)
		{
			uint32_t key = Canvas::CalculateKey(aType);
			Canvas::RegisterCanvas(key, dynamic_cast<UICanvas* const>(aCanvas));
		}

		template<typename Type>
		void TransitionTo(const Type aType, const bool aKeepUpdatingPreviousCanvas = false, const bool aKeepRenderingPreviousCanvas = false) {
			uint32_t key = Canvas::CalculateKey(aType);
			Canvas::TransitionTo(key, aKeepUpdatingPreviousCanvas, aKeepRenderingPreviousCanvas);
		}

		template<typename Type>
		void ResetTo(const Type aType) {
			uint32_t key = Canvas::CalculateKey(aType);
			Canvas::ResetTo(key);
		}

		template<typename Key>
		uint32_t CalculateKey(const Key aKey)
		{
			static_assert(std::is_enum<Key>::value, "Corresponding type is not an enum!");

			uint32_t id = static_cast<uint32_t>(typeid(Key).hash_code());
			uint32_t key = static_cast<uint32_t>(aKey);
			return id + key;
		}

	}

	namespace UI
	{
		class IMGuiContext
		{
		private:
			void InitText();

		private: //Data to handle gui elements
			std::unordered_map<uint32_t, std::vector<std::shared_ptr<UIContent>>> myGuiContent;
			uint32_t myCurrentCanvasID;
			uint32_t myLocalID;
		private://Friends <3
			friend void Begin(UICanvas* const aCanvasPtr);
			friend void Text(std::string someText, Tga::Vector2f aPosition, const float aSize = 1.0f, Tga::Color aColor = Tga::Color(0, 1, 1, 1));
			friend void End();
			friend void Init();
		private: //Getters/Setters
			friend std::unordered_map<uint32_t, std::vector<std::shared_ptr<UIContent>>>& GuiContent();
		};
		inline IMGuiContext imguiContext;

		void Init();
		void Begin(UICanvas* const aCanvasPtr);
		void Text(std::string someText, Tga::Vector2f aPosition, Tga::Color aColor);
		void End();

		const Tga::Vector2f GetViewSize();

	}



}


