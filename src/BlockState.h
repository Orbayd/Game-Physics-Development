#ifndef BLOCK_STATE_H
#define BLOCK_STATE_H

#include "OinkEvent.h"
#include "Blink.h"
#include "TimerMan.h"
#include "Simulation.h"
#include "Block.h"

class BlockState
{
public:


	virtual void Enter(Block* pBlock) = 0;
	virtual void Execute(float totalTime, Block * pPiggy) = 0;
	virtual void Exit(Block* pBlock) = 0;

private:

};

#endif