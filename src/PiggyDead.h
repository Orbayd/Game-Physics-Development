#ifndef PIGGY_DEAD_H
#define PIGGY_DEAD_H
#include "PiggyState.h"

class PiggyDead : public PiggyState
{
public:
	PiggyDead();
	~PiggyDead();
	void Enter(Piggy* pBird) override;
	void Exit(Piggy* pBird) override;
	void Execute(float totalTime, Piggy* pBird) override;
	static PiggyDead * GetInstance();
private:

};




#endif