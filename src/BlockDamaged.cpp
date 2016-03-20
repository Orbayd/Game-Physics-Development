
#include "BlockDamaged.h"
#include "BlockHeavyDamaged.h"
BlockDamaged::BlockDamaged()
{
}

BlockDamaged::~BlockDamaged()
{
}
BlockDamaged *BlockDamaged::GetInstance()
{
	static BlockDamaged instance;
	return &instance;
}
void BlockDamaged::Enter(Block* pBlock)
{
	pBlock->goNextPhase();
}

void BlockDamaged::Execute(float totalTime, Block* pBlock)
{
	if (pBlock->damage >= (pBlock->maxDamage*0.50f - 0.01f))
	{
		pBlock->ChangeState(BlockHeavyDamaged::GetInstance());
	}
	totalTime;
}
void BlockDamaged::Exit(Block* pBlock)
{
	pBlock;
}