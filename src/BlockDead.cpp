

#include "BlockDead.h"
BlockDead::BlockDead()
{
}

BlockDead::~BlockDead()
{
}
BlockDead *BlockDead::GetInstance()
{
	static BlockDead instance;
	return &instance;
}
void BlockDead::Enter(Block* pBlock)
{
	pBlock; pBlock->DeadPhase();
}

void BlockDead::Execute(float totalTime, Block* pBlock)
{
	pBlock;
	totalTime;
}
void BlockDead::Exit(Block* pBlock)
{
	pBlock;
}