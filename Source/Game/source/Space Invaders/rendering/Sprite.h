#pragma once
#include <tge/sprite/sprite.h>

namespace si
{
	struct Sprite
	{
		const wchar_t* mySpritePath = L"Sprites/tge_logo_w.dds";
		Tga::Vector2f mySizeOffset;
		Tga::Vector2f myPivot = {0.5f, 0.5f};
		Tga::Vector2f mySize;
		Tga::Color myColor = { 1,1,1,1 };
	};
}