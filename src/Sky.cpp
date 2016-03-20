#include "Sky.h"
#include "GameObjectMan.h"
Sky::~Sky()
{
}

Sky::Sky(GameObjectName::Name name, GraphicsObject_Sprite *pSprite, GameSortBucket *pSort) : GameObject2D(name, pSprite)
{
	GameObjectMan::Add(this, pSort);

}
Sky* Sky::Create(GameObjectName::Name gObjName, ImageName::Name imageName, Rect rect)
{

	GameObject *pObj = GameObjectMan::Find(GameObjectName::BackGround_Sort);
	assert(pObj);
	GameSortBucket *pSortBucket = (GameSortBucket *)pObj;

	GraphicsObject_Sprite *pSprite = new GraphicsObject_Sprite(imageName, rect);
	Sky *pSky = new Sky(gObjName, pSprite, pSortBucket);

	return pSky;
}
