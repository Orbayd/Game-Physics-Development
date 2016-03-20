#include "BackGround.h"
#include "GameObjectMan.h"



BackGround::~BackGround()
{
	
}
BackGround::BackGround(GameObjectName::Name name, GraphicsObject_Sprite *pSprite, GameSortBucket *pSort) : GameObject2D(name,pSprite)
{
	GameObjectMan::Add(this, pSort);
}