#ifndef STONEBLOCK_H
#define STONEBLOCK_H

#include "GameObject2D.h"
#include "GameSortBucket.h"
#include "Block.h"

class StoneBlock : public Block
{
public:
	// Create
	StoneBlock(GameObjectName::Name name, GraphicsObject_Sprite *pSprite, GameSortBucket *pSort);
	void ApplyDamage();
	virtual void WorldUpdate(float currentTime) override;
	static StoneBlock * Create(GameObjectName::Name gObjName, ImageName::Name imageName, Rect rect,float angle, b2BodyType type);
	virtual ~StoneBlock();
	virtual void DeadPhase()override;
	void CreateChunks() override;
	//float scaleFactor;
private:
	StoneBlock();

};

#endif