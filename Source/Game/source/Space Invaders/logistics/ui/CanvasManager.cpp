#include "CanvasManager.h"
#include "framework/UICanvas.h"

#include "../factories/UIFactory.h"
#include "../../Entity.h"
#include "../scene management/SceneManager.h"

#include <tge/engine.h>


namespace si
{
	namespace UI
	{
		void RegisterCanvas(const uint32_t anID, UICanvas* aCanvas)
		{
			canvases[anID] = std::shared_ptr<UICanvas>(aCanvas);
		}

		void TransitionToCanvas(const uint32_t anID, const bool anUpdatePreviousCanvas, const bool aRenderPreviousCanvas)
		{



			if (!anUpdatePreviousCanvas)
			{
				uint32_t prevKey = updateStack.top();
				canvases[prevKey]->OnTransitionExit();
				updateStack.pop();
			}

			if (!aRenderPreviousCanvas)
				renderStack.pop();

			canvases[anID]->OnTransitionEnter();
			updateStack.push(anID);
			renderStack.push(anID);
		}

		void TransitionBack()
		{
			if (!updateStack.empty())
				updateStack.pop();

			if (!renderStack.empty())
				renderStack.pop();
		}

		void ResetToCanvas(const uint32_t anID)
		{
			while (!updateStack.empty())
				updateStack.pop();

			while (!renderStack.empty())
				renderStack.pop();

			TransitionToCanvas(anID, false, false);
		}

		void UpdateCanvasStack(const float aDT)
		{
			auto cpy = updateStack;

			while (!cpy.empty())
			{
				canvases[cpy.top()]->OnUpdate(aDT);
				cpy.pop();
			}
		}

		void RenderCanvasStack()
		{
			auto cpy = renderStack;

			while (!cpy.empty())
			{
				canvases[cpy.top()]->Render();
				cpy.pop();
			}
		}
		void Begin(UICanvas* const aCanvas)
		{
			currentCanvas = aCanvas->GetID();
		}
		void End()
		{
			currentCanvas = UINT32_MAX;
		}
		void Text(const std::string& someText, Tga::Vector2f aPosition)
		{
			if (currentCanvas == UINT32_MAX) return;

			auto& scene = *SceneManager::GetUIScene();




			UIContent* content = UIFactory::GetElement(UIType::Text);
			content->AssignCanvas(canvases[currentCanvas].get());
			content->ApplyContent(someText);
			content->GetEntity()->myTransform.Position() = Tga::Vector3f(aPosition.x, aPosition.y, 0);
		}
		void Button(const std::string& someText, Tga::Vector2f aPosition, std::function<void()> aCallback)
		{
			if (currentCanvas == UINT32_MAX) return;

			UIContent* content = UIFactory::GetElement(UIType::Button);
			content->AssignCanvas(canvases[currentCanvas].get());
			content->ApplyContent(someText);
			content->ApplyContent(aCallback);
			content->GetEntity()->myTransform.Position() = Tga::Vector3f(aPosition.x, aPosition.y, 0);
		}
		Tga::Vector2f GetViewSize()
		{
			auto engine = Tga::Engine::GetInstance();
			auto res = engine->GetRenderSize();
			return Tga::Vector2f(static_cast<float>(res.x), static_cast<float>(res.y));
		}
		void RegisterCanvas(const uint32_t anID, UICanvas* aCanvas)
		{
			canvases[anID] = std::shared_ptr<UICanvas>(aCanvas);
		}
	}
}



