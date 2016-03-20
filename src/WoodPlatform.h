#ifndef WOODPLATFORM_H
#define WOODPLATFORM_H

#include "GameObject2D.h"
#include "GameSortBucket.h"
class WoodPlatform : public GameObject2D
{
public:
	
	
	WoodPlatform(GameObjectName::Name name, GraphicsObject_Sprite *pSprite, GameSortBucket *pSort);
	virtual void WorldUpdate(float currentTime) override;
	virtual ~WoodPlatform();
	float scaleFactor;
private:
	WoodPlatform();
};



#endif