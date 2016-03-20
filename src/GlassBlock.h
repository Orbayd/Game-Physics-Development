#ifndef GLASSBLOCK_H
#define GLASSBLOCK_H

#include "GameObject2D.h"
#include "GameSortBucket.h"
#include "Block.h"

class GlassBlock : public Block
{
public:
	// Create
	GlassBlock(GameObjectName::Name name, GraphicsObject_Sprite *pSprite, GameSortBucket *pSort);
	void ApplyDamage();
	virtual void WorldUpdate(float currentTime) override;

	virtual ~GlassBlock();
	void CreateChunks() override;
	virtual void DeadPhase()override;
	//float scaleFactor;
private:
	GlassBlock();

};

#endif