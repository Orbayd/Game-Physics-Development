#ifndef STONE_BALL_H
#define STONE_BALL_H
#include "Block.h"
class StoneBall :public Block
{
public:
	StoneBall(GameObjectName::Name name, GraphicsObject_Sprite *pSprite, GameSortBucket *pSort);
	
	~StoneBall();
	virtual void WorldUpdate(float currentTime) override;
	static StoneBall * Create(GameObjectName::Name gObjName, ImageName::Name imageName, Rect rect, b2BodyType type);
private:
	StoneBall();

};




#endif