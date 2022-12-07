#include "CanvasManager.h"
#include "framework/UICanvas.h"

void si::RegisterCanvas(const uint32_t anID, UICanvas* aCanvas)
{
	canvases[anID] = std::shared_ptr<UICanvas>(aCanvas);
}

void si::TransitionTo(const uint32_t anID, const bool anUpdatePreviousCanvas, const bool aRenderPreviousCanvas)
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

void si::TransitionBack()
{
	if (!updateStack.empty())
		updateStack.pop();

	if (!renderStack.empty())
		renderStack.pop();
}

void si::ResetTo(const uint32_t anID)
{
	while (!updateStack.empty())
		updateStack.pop();

	while (!renderStack.empty())
		renderStack.pop();

	TransitionTo(anID, false, false);
}

void si::UpdateCanvasStack(const float aDT)
{
	auto cpy = updateStack;

	while (!cpy.empty())
	{
		canvases[cpy.top()]->OnUpdate(aDT);
		cpy.pop();
	}
}

void si::RenderCanvasStack()
{
	auto cpy = renderStack;

	while (!cpy.empty())
	{
		canvases[cpy.top()]->Render();
		cpy.pop();
	}
}

