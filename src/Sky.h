#ifndef SKY_H
#define SKY_H
#include "GameObject2D.h"
#include "GameSortBucket.h"
class Sky : public GameObject2D
{
public:
	static Sky* Create(GameObjectName::Name gObjName, ImageName::Name imageName, Rect rect);
	~Sky();

private:
	Sky(GameObjectName::Name name, GraphicsObject_Sprite *pSprite, GameSortBucket *pSort);
	Sky();
};



#endif