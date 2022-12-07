#pragma once

namespace si
{
	class UICanvas
	{
	public:
		virtual void OnInit() {};
		virtual void OnUpdate(const float /*aDT*/) {};
		virtual void OnTransitionEnter() {};
		virtual void OnTransitionExit() {};
	};
}