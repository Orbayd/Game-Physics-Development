#include "BlockHealty.h"
#include "BlockDamaged.h"

BlockHealty::BlockHealty()
{
}

BlockHealty::~BlockHealty()
{
}
BlockHealty *BlockHealty::GetInstance()
{
	static BlockHealty instance;
	return &instance;
}
void BlockHealty::Enter(Block* pBlock)
{
	pBlock;
}

void BlockHealty::Execute(float totalTime, Block* pBlock)
{
	if (pBlock->damage >= (pBlock->maxDamage*0.25f - 0.01f))
	{
		pBlock->ChangeState(BlockDamaged::GetInstance());
	}
	pBlock;
	totalTime;
}
void BlockHealty::Exit(Block* pBlock)
{
	pBlock;
}