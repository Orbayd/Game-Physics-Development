#include "BlockHeavyDamaged.h"


BlockHeavyDamaged::BlockHeavyDamaged()
{
}

BlockHeavyDamaged::~BlockHeavyDamaged()
{
}
BlockHeavyDamaged *BlockHeavyDamaged::GetInstance()
{
	static BlockHeavyDamaged instance;
	return &instance;
}
void BlockHeavyDamaged::Enter(Block* pBlock)
{
	pBlock;
	pBlock->goNextPhase();
}

void BlockHeavyDamaged::Execute(float totalTime, Block* pBlock)
{
	pBlock;
	totalTime;
	if (pBlock->damage >= (pBlock->maxDamage - 0.01f))
	{
		pBlock->DeadPhase();
	}
}
void BlockHeavyDamaged::Exit(Block* pBlock)
{
	pBlock;
}