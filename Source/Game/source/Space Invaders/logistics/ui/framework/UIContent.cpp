#include "UIContent.h"

void si::UIContent::Render()
{
	if (myRenderCall)
		(*myRenderCall)(myCanvas, this);
}
