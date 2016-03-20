#ifndef WOODBLOCK_H
#define WOODBLOCK_H

#include "GameObject2D.h"
#include "Block.h"
#include "GameSortBucket.h"

class ChunkEmitter;
class WoodBlock : public Block
{
public:
	// Create
	WoodBlock(GameObjectName::Name name, GraphicsObject_Sprite *pSprite, GameSortBucket *pSort);
	
	void ApplyDamage();
	virtual void WorldUpdate(float currentTime) override;
	void CreateChunks() override;
	virtual ~WoodBlock();
	virtual void DeadPhase()override;
	//float scaleFactor;
private:
	WoodBlock();
	//ChunkEmitter *pEmitter;
};

#endif