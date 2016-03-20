#ifndef BLOCK_HEAVY_DAMAGED_H
#define BLOCK_HEAVY_DAMAGED_H
#include "BlockState.h"

class BlockHeavyDamaged : public BlockState
{
public:
	BlockHeavyDamaged();
	~BlockHeavyDamaged();
	void Enter(Block* pBird) override;
	void Exit(Block* pBird) override;
	void Execute(float totalTime, Block* pBird) override;
	static BlockHeavyDamaged * GetInstance();
private:

};
#endif