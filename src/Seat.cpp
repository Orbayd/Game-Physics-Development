#include "Seat.h"
#include "GameObjectMan.h"
#include "DebugOut.h"
#include "AzulHelper.h"
#include "World.h"
Seat::Seat(GameObjectName::Name name, GraphicsObject_Sprite *pSprite, GameSortBucket *pSort)
	:GameObject2D(name, pSprite)
{
	
	GameObjectMan::Add(this, pSort);
}

Seat::~Seat()
{

}
void Seat::SetAnchorPoint(const float x, const float y)
{
	anchorX = x;
	anchorY = y;
}
void Seat::Join(GameObject2D * pBird)
{
	pBird;
}