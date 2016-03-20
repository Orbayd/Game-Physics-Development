#ifndef BLOCK_DEAD_H
#define BLOCK_DEAD_H
#include "BlockState.h"

class BlockDead: public BlockState
{
public:
	BlockDead();
	~BlockDead();
	void Enter(Block* pBird) override;
	void Exit(Block* pBird) override;
	void Execute(float totalTime, Block* pBird) override;
	static BlockDead * GetInstance();
private:

};
#endif