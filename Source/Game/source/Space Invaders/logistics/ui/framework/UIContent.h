#pragma once
#include "../../../Component.h"

#include <functional>
#include <string>

namespace Tga 
{
	class Text;
	struct Sprite2DInstanceData;
}

namespace si
{
	class UICanvas;

	enum class UIType
	{
		Text, Button
	};

	

	class UIContent : public Component
	{
		friend class UIFactory;
	public:
		union Content {
			std::string myText;
			float myDecimal;
			int myDigit;
			std::function<void()> myEvent;
		};
		union Interface 
		{
			Tga::Text* myTextInterface;
			const char* myImagePath;
		};
	public: //Setter and Getters
		inline void AssignCanvas(UICanvas* aCanvas) { myCanvas = aCanvas; }
		inline void Listen(std::function<void(UICanvas*, UIContent*)>* const anOnRenderCallback) { myRenderCall = anOnRenderCallback; }
		inline Entity* const GetEntity() { return myEntity; }
	public: //Core
		void Render();
	public:
		template<typename Type>
		inline void ApplyContent(const Type& someData) {};
		template<>
		inline void ApplyContent<std::string>(const std::string& someText)
		{
			myContent.myText = someText;
		}
		template<>
		inline void ApplyContent<float>(const float& someDecimal)
		{
			myContent.myDecimal = someDecimal;
		}
		template<>
		inline void ApplyContent<int>(const int& someDigit)
		{
			myContent.myDigit = someDigit;
		}
		template<>
		inline void ApplyContent<std::function<void()>>(const std::function<void()>& someCallback)
		{
			myContent.myEvent = someCallback;
		}

	private:
		std::function<void(UICanvas*, UIContent*)>* myRenderCall;
		UICanvas* myCanvas;
	private://Data
		Content myContent;
		Interface myInterface;
	};
}