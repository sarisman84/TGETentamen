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

	typedef std::variant<std::shared_ptr<Tga::Text>, const char*> Interface;

	class UIContent
	{
	public: //Render Logic
		void Render();
	public:
		inline Interface& EditInterface() { return myInterface; }

	private://Data
		Interface myInterface;
		/*	Content myContent;
			Interface myInterface;*/
	};
}