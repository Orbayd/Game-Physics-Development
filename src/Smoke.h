#ifndef SMOKE_H
#define SMOKE_H
#include "GameObject2D.h"

class GameSortBucket;
class  Smoke : public GameObject2D
{
public:
	Smoke(GameObjectName::Name name, GraphicsObject_Sprite *pSprite, GameSortBucket *pSort);
	~Smoke();
	virtual void WorldUpdate(float currentTime)override;
private:

};



#endif
