#pragma once
#include <vector>

namespace si
{
	class UICanvas
	{
	public:
		virtual void OnInit() {};
		virtual void OnUpdate(const float /*aDT*/) {};
		virtual void OnTransitionEnter() {};
		virtual void OnTransitionExit() {};
	private:
		friend void RenderCanvasStack();
		void Render();
		std::vector<uint32_t> myUIElements;
	};
}