#pragma once
#include "../../../Component.h"

#include <tge/math/vector2.h>
#include <tge/text/text.h>

#include <memory>
#include <functional>
#include <string>
#include <variant>

#pragma warning(disable: 4624) //Union warning

namespace Tga
{
	struct Sprite2DInstanceData;
}

namespace si
{
	class UICanvas;

	enum class UIType
	{
		Text, Button
	};

	typedef std::variant<std::string, float, int, std::function<void()>> Content;
	typedef std::variant<std::shared_ptr<Tga::Text>, const char*> Interface;

	class UIContent
	{
	public: //Render Logic
		void Render();
	public: //Setters (with union specifiers)
		template<typename Type>
		inline void ApplyContent(const Type& someData) {};
		template<>
		inline void ApplyContent<std::string>(const std::string& someText)
		{
			std::get<std::string>(myContent) = someText;
		}
		template<>
		inline void ApplyContent<float>(const float& someDecimal)
		{
			std::get<float>(myContent) = someDecimal;
		}
		template<>
		inline void ApplyContent<int>(const int& someDigit)
		{
			std::get<int>(myContent) = someDigit;
		}
		template<>
		inline void ApplyContent<std::function<void()>>(const std::function<void()>& someCallback)
		{
			std::get<std::function<void()>>(myContent) = someCallback;
		}

	public:
		inline Interface& EditInterface() { return myInterface; }

	private://Data
		Content myContent;
		Interface myInterface;
		/*	Content myContent;
			Interface myInterface;*/
	};
}