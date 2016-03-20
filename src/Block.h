#ifndef BLOCK_H
#define BLOCK_H

#include "GameObject2D.h"
#include "GameSortBucket.h"
#include "ImageName.h"
#include "SoundObject.h"
class BlockState;
class ChunkEmitter;

class Block : public GameObject2D
{
public:
	// Create
	Block(GameObjectName::Name name, GraphicsObject_Sprite *pSprite, GameSortBucket *pSort);
	
	virtual void WorldUpdate(float currentTime) override;
	virtual ~Block();
	
	void ApplyDamage();
	virtual void DeadPhase();
	virtual void CreateChunks(){};
	void ChangeState(BlockState *pState);
	void goNextPhase();
	float scaleFactor;
	
private:
	Block();
protected:
	BlockState* pBlockState;
	ChunkEmitter * pEmitter;
	SoundObject *pBlockSound;
};

#endif