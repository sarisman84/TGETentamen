#include "UIFactory.h"
#include "../scene management/SceneManager.h"
#include "../../Scene.h"
#include "../../Entity.h"

#include <tge/text/text.h>

si::UIFactory::UIFactory()
{
	ourInstance = this;

	UIContentBlueprint textType = {};
	textType.myCreationEvent = [](UIContent* someContent)
	{
		auto text = new Tga::Text();
		auto pos = someContent->GetEntity()->myTransform.Position();
		text->SetPosition({ pos.x, pos.y });
		someContent->myInterface.myTextInterface = text;
	};
	textType.myRenderEvent = [](UICanvas* aCanvas, UIContent* someContent) {
		someContent->myInterface.myTextInterface->SetText(someContent->myContent.myText);
	};
	AddType(UIType::Text, textType);
	AddType(UIType::Button, textType);
}

si::UIContent* si::UIFactory::GetElement(const uint32_t anID)
{
	auto scene = SceneManager::GetUIScene();
	scene;
	auto entity = new Entity();
	auto& content = entity->AddComponent<UIContent>();
	content.Listen(&myUITypes[anID].myRenderEvent);
	return &content;
}

void si::UIFactory::AddType(const uint32_t anID, const UIContentBlueprint& anOnRenderCallback)
{
	myUITypes[anID] = anOnRenderCallback;
}
