#ifndef HEALTY_H
#define HEALTY_H
#include "PiggyState.h"

class PiggyHealty : public PiggyState
{
public:
	PiggyHealty();
	~PiggyHealty();
	void Enter(Piggy* pBird) override;
	void Exit(Piggy* pBird) override;
	void Execute(float totalTime, Piggy* pBird) override;
	static PiggyHealty * GetInstance();
private:

};




#endif