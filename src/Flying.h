#ifndef FLYING_H
#define FLYING_H
#include "BirdState.h"

class Fly : public BirdState
{
public:
	Fly();
	~Fly();
	void Enter(Bird* pBird) override;
	void Exit(Bird* pBird) override;
	void Execute(float totalTime, Bird* pBird) override;
	static Fly* GetInstance();
private:
	
};




#endif