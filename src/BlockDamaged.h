#ifndef BLOCK_DAMAGED_H
#define BLOCK_DAMAGED_H
#include "BlockState.h"

class BlockDamaged : public BlockState
{
public:
	BlockDamaged();
	~BlockDamaged();
	void Enter(Block* pBird) override;
	void Exit(Block* pBird) override;
	void Execute(float totalTime, Block* pBird) override;
	static BlockDamaged * GetInstance();
private:

};
#endif