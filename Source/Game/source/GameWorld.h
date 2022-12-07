#pragma once
#include "Space Invaders/Scene.h"

class GameWorld
{
public:
	GameWorld(); 
	~GameWorld();

	void Init();
	void Update(float aTimeDelta); 
	void Render();
private:
	Tga::Sprite2DInstanceData myTGELogoInstance = {};
	Tga::SpriteSharedData sharedData = {};

private: //Space Invaders
	si::Scene myTestScene;
};