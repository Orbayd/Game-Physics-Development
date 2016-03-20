#ifndef SLINGSHOT_H
#define SLINGSHOT_H
#include "GameObject2D.h"
#include "GameSortBucket.h"
class SlingShot : public GameObject2D
{
public:
	SlingShot(GameObjectName::Name name, GraphicsObject_Sprite *pSprite);

	
	virtual ~SlingShot();

private:
	SlingShot();
};



#endif