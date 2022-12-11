#include "CanvasManager.h"
#include "framework/UICanvas.h"

#include "../../Entity.h"
#include "../scene management/SceneManager.h"
#include "../logging/Logger.h"

#include <tge/engine.h>
#include <tge/text/text.h>
#include "framework/UIContent.h"

namespace si
{
	namespace UI
	{
		void Init()
		{
			imguiContext = IMGuiContext();
			imguiContext.myCurrentCanvasID = UINT32_MAX;
		}
		std::unordered_map<uint32_t, std::vector<std::shared_ptr<UIContent>>>& GuiContent()
		{
			return imguiContext.myGuiContent;
		}
		void Begin(UICanvas* const aCanvasPtr)
		{
			if (!aCanvasPtr)
			{
				ERROR_LOG("No Canvas found! Exiting");
				return;
			}

			imguiContext.myCurrentCanvasID = aCanvasPtr->GetID();
			imguiContext.myLocalID = 0;
		}
		void Text(std::string someText, Tga::Vector2f aPosition, Tga::Color aColor)
		{
			//If this is called in an non-canvas enviroment, exit
			if (imguiContext.myCurrentCanvasID == UINT32_MAX)
			{
				ERROR_LOG("Attempting to render text in a non-canvas enviroment!");
				return;
			}
			if (imguiContext.myGuiContent.count(imguiContext.myCurrentCanvasID) == 0 ||
				imguiContext.myLocalID >= imguiContext.myGuiContent[imguiContext.myCurrentCanvasID].size())
			{
				LOG("Text Element missing: Initializing.");
				//Initialize element
				imguiContext.InitText();
			}

			//Apply its content
			auto content = imguiContext.myGuiContent[imguiContext.myCurrentCanvasID][imguiContext.myLocalID];
			auto textInt = std::get <std::shared_ptr<Tga::Text>>(content->EditInterface());
			textInt->SetColor(aColor);
			textInt->SetPosition(aPosition);
			textInt->SetText(someText);

			imguiContext.myLocalID++;
		}
		void End()
		{
			imguiContext.myCurrentCanvasID = UINT32_MAX;
		}

		const Tga::Vector2f GetViewSize()
		{
			auto engine = Tga::Engine::GetInstance();
			return Tga::Vector2f(static_cast<float>(engine->GetRenderSize().x), static_cast<float>(engine->GetRenderSize().y));
		}

		void IMGuiContext::InitText()
		{
			uint32_t key = imguiContext.myCurrentCanvasID;
			auto content = std::make_shared<UIContent>();
			auto text = std::get<std::shared_ptr<Tga::Text>>(content->EditInterface()) = std::make_shared<Tga::Text>();
			imguiContext.myGuiContent[key].push_back(content);
			LOG("Created Text Element!");
		}
	}
}

void si::Canvas::RegisterCanvas(const uint32_t anID, UICanvas* const aCanvas)
{
	aCanvas->OnInit();
	canvasContext.myCanvases[anID].reset(aCanvas);
}

void si::Canvas::TransitionTo(const uint32_t anID, const bool aKeepUpdatingPreviousCanvas, const bool aKeepRenderingPreviousCanvas)
{
	if (!canvasContext.myCanvasStack.empty())
		canvasContext.myCanvases[canvasContext.myCanvasStack.top()]->OnTransitionExit();

	if (!aKeepUpdatingPreviousCanvas && !canvasContext.myCanvasStack.empty()) {
		canvasContext.myCanvasStack.pop();
	}
	canvasContext.myCanvasStack.push(anID);


	if (!aKeepRenderingPreviousCanvas && !canvasContext.myRenderStack.empty()) {
		canvasContext.myRenderStack.pop();
	}
	canvasContext.myRenderStack.push(anID);

	canvasContext.myCanvases[anID]->OnTransitionEnter();
}

void si::Canvas::TransitionBack()
{
	if (!canvasContext.myRenderStack.empty())
	{
		canvasContext.myRenderStack.pop();
	}

	if (!canvasContext.myCanvasStack.empty())
	{
		canvasContext.myCanvases[canvasContext.myCanvasStack.top()]->OnTransitionExit();
		canvasContext.myCanvasStack.pop();
	}
	if (!canvasContext.myCanvasStack.empty())
		canvasContext.myCanvases[canvasContext.myCanvasStack.top()]->OnTransitionEnter();
}

void si::Canvas::ResetTo(const uint32_t anID)
{
	while (!canvasContext.myCanvasStack.empty())
	{
		canvasContext.myCanvases[canvasContext.myCanvasStack.top()]->OnTransitionExit();
		canvasContext.myCanvasStack.pop();
	}

	while (!canvasContext.myRenderStack.empty())
	{
		canvasContext.myRenderStack.pop();
	}

	TransitionTo(anID);
}

void si::Canvas::Init()
{
	canvasContext = CanvasContext();
}

void si::Canvas::Update(const float aDT)
{
	auto stack = canvasContext.myCanvasStack;
	while (!stack.empty())
	{
		auto index = stack.top();
		stack.pop();

		canvasContext.myCanvases[index]->OnUpdate(aDT);
	}
}

void si::Canvas::Render()
{
	auto stack = canvasContext.myRenderStack;
	while (!stack.empty())
	{
		auto index = stack.top();
		stack.pop();

		auto& elements = UI::GuiContent()[canvasContext.myCanvases[index]->GetID()];
		for (auto& element : elements)
		{
			element->Render();
		}
	}
}
