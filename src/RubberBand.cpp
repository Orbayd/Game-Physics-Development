#include "RubberBand.h"
#include "GameObjectMan.h"
#include "DebugOut.h"
#include "AzulHelper.h"

RubberBand::RubberBand(GameObjectName::Name name, GraphicsObject_Quad *pQuad, GameSortBucket *pSort)
	:GameObject2D(name, pQuad)
{
	Vect(0, 0, 0, 0);
	GameObjectMan::Add(this, pSort);
}

RubberBand::~RubberBand()
{

}
void RubberBand::SetAnchorPoint(const float x, const float y)
{
	anchorX = x;
	anchorY = y;
}


