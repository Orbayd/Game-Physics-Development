#ifndef HELMET_H
#define HELMET_H
#include "GameObject2D.h"
class GameSortBucket;
class Helmet : public GameObject2D 
{
public:
	
	~Helmet();
	static Helmet *Create(GameObjectName::Name gObjName, ImageName::Name imageName, Rect rect);
	
	virtual void WorldUpdate(float currentTime) override;
private:
	Helmet(GameObjectName::Name name, GraphicsObject_Sprite *pSprite, GameSortBucket *pSort);
	Helmet();
};




#endif