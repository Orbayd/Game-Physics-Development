#include "SmokeFactory.h"
#include "Smoke.h"
#include "GraphicsObject.h"
Smoke * SmokeFactory::Create(ImageName::Name imageName, Rect rect, GameSortBucket * pSort)
{
	//Create Sprite
	GraphicsObject_Sprite *pSprite = new GraphicsObject_Sprite(imageName, rect);
	assert(pSprite);
	//Create Smoke	
	Smoke *pSmoke = new Smoke(GameObjectName::Smoke, pSprite, pSort);

	return pSmoke;


}