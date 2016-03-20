#ifndef BACKGROUND_H
#define BACKGROUND_H
#include "GameObject2D.h"
#include "GameSortBucket.h"
class Ground;
class BackGround : public GameObject2D
{
public:
	 BackGround(GameObjectName::Name name, GraphicsObject_Sprite *pSprite, GameSortBucket *pSort);
	 ~BackGround();
	 Ground *pGround;
private:
	BackGround();
	
};





#endif