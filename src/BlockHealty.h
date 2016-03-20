#ifndef BLOCK_HEALTY_H
#define BLOCK_HEALTY_H
#include "BlockState.h"

class BlockHealty : public BlockState
{
public:
	BlockHealty();
	~BlockHealty();
	void Enter(Block* pBird) override;
	void Exit(Block* pBird) override;
	void Execute(float totalTime, Block* pBird) override;
	static BlockHealty * GetInstance();
private:

};




#endif