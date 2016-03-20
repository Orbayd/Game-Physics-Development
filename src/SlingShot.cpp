#include "SlingShot.h"
#include "GameObjectMan.h"

SlingShot::~SlingShot()
{

}

SlingShot::SlingShot(GameObjectName::Name name, GraphicsObject_Sprite *pSprite) : GameObject2D(name, pSprite)
{
	//pGraphics_Sprite = new GraphicsObject_Sprite(ImageName::SlingshotFront, Rect(150, 265, 40 * scalefactor, 200 * scalefactor));
	//GameObject2D * pSlingFront = new GameObject2D(GameObjectName::SlingShootFront, pGraphics_Sprite);
	//GameObjectMan::Add(pSlingFront, pSlingFrontSort);
	//pSlingFront->setParent(0);

	//pGraphics_Sprite = new GraphicsObject_Sprite(ImageName::SlingshotBack, Rect(132, 300, 40 * scalefactor, 125 * scalefactor));
	//GameObject2D * pSlingBack = new GameObject2D(GameObjectName::SlingShootBack, pGraphics_Sprite);
	//GameObjectMan::Add(pSlingBack, pSlingBackSort);
	//pSlingBack->setParent(0);
	//
	
	//GameObjectMan::Add(this, pSort);


}