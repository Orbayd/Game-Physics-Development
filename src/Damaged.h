#ifndef DAMAGED_H
#define DAMAGED_H
#include "PiggyState.h"

class PiggyDamaged : public PiggyState
{
public:
	PiggyDamaged();
	~PiggyDamaged();
	void Enter(Piggy* pBird) override;
	void Exit(Piggy* pBird) override;
	void Execute(float totalTime, Piggy* pBird) override;
	static PiggyDamaged * GetInstance();
private:

};




#endif