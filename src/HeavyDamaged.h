#ifndef HEAVY_DAMAGED_H
#define HEAVY_DAMAGED_H
#include "PiggyState.h"

class PiggyHeavyDmged : public PiggyState
{
public:
	PiggyHeavyDmged();
	~PiggyHeavyDmged();
	void Enter(Piggy* pBird) override;
	void Exit(Piggy* pBird) override;
	void Execute(float totalTime, Piggy* pBird) override;
	static PiggyHeavyDmged * GetInstance();
private:

};




#endif