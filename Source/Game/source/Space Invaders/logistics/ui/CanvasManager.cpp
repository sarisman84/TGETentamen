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
		void Text(std::string someText, Tga::Vector2f aPosition, const float aSize, Tga::Color aColor)
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
				//LOG("Text Element missing: Initializing.");
				//Initialize element
				imguiContext.InitText();
			}

			//Apply its content
			auto content = imguiContext.myGuiContent[imguiContext.myCurrentCanvasID][imguiContext.myLocalID];
			auto textInt = std::get <std::shared_ptr<Tga::Text>>(content->EditInterface());
			textInt->SetColor(aColor);
			textInt->SetPosition(aPosition);
			textInt->SetText(someText);
			textInt->SetScale(aSize);

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
			//LOG("Created Text Element!");
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
	{
		auto key = std::get<uint32_t>(canvasContext.myCanvasStack.top());
		canvasContext.myCanvases[key]->OnTransitionExit();
	}

	canvasContext.myCanvasStack.push(std::make_tuple(anID, aKeepUpdatingPreviousCanvas));
	canvasContext.myRenderStack.push(std::make_tuple(anID, aKeepRenderingPreviousCanvas));

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
		auto key = std::get<uint32_t>(canvasContext.myCanvasStack.top());
		canvasContext.myCanvases[key]->OnTransitionExit();
		canvasContext.myCanvasStack.pop();
	}
	if (!canvasContext.myCanvasStack.empty())
	{
		auto key = std::get<uint32_t>(canvasContext.myCanvasStack.top());
		canvasContext.myCanvases[key]->OnTransitionEnter();
	}

}

void si::Canvas::ResetTo(const uint32_t anID)
{
	while (!canvasContext.myCanvasStack.empty())
	{
		auto key = std::get<uint32_t>(canvasContext.myCanvasStack.top());
		canvasContext.myCanvases[key]->OnTransitionExit();
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
	bool updateFlag = true;
	while (!stack.empty())
	{
		auto index = stack.top();
		stack.pop();
		if (!updateFlag) continue;

		canvasContext.myCanvases[std::get<uint32_t>(index)]->OnUpdate(aDT);
		updateFlag = std::get<bool>(index);
	}
}

void si::Canvas::Render()
{
	auto stack = canvasContext.myRenderStack;
	bool renderFlag = true;
	while (!stack.empty())
	{
		auto index = stack.top();
		stack.pop();

		if (!renderFlag) continue;
		auto& elements = UI::GuiContent()[canvasContext.myCanvases[std::get<uint32_t>(index)]->GetID()];
		for (auto& element : elements)
		{
			element->Render();
		}
		elements.clear();
		renderFlag = std::get<bool>(index);
	}
}
