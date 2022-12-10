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
	public:
		void Render();
	public:
		inline const uint32_t GetID() { return 0; }
	private:
		std::vector<uint32_t> myUIElements;
		uint32_t myID;

	};
}