#ifndef PIGGY_STATE_H
#define PIGGY_STATE_H

#include "OinkEvent.h"
#include "Blink.h"
#include "TimerMan.h"
#include "Simulation.h"
#include "Piggy.h"

class PiggyState
{
public:


	virtual void Enter(Piggy* pPiggy) = 0;
	virtual void Execute(float totalTime, Piggy * pPiggy) = 0;
	virtual void Exit(Piggy* pPiggy) = 0;

private:

};

#endif

