#include "UIContent.h"
void si::UIContent::Render()
{
	if (std::shared_ptr<Tga::Text> text = std::get<std::shared_ptr<Tga::Text>>(myInterface))
		text->Render();
}
