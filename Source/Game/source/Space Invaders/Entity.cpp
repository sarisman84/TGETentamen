#include "Entity.h"
#include <tge/engine.h>

const bool si::Entity::IsInRenderView()
{
	auto engine = Tga::Engine::GetInstance();
	auto resolution = engine->GetRenderSize();
	auto pos = myTransform.Position();
	auto size = mySprite.mySize;

	auto halfExtends = size / 2.0f;

	return
		pos.x + halfExtends.x > 0 &&
		pos.y + halfExtends.y > 0 &&
		pos.x - halfExtends.x < resolution.x&&
		pos.y - halfExtends.y < resolution.y;
}
