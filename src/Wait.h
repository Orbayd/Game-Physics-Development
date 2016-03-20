#ifndef WAIT_H
#define WAIT_H
#include "BirdState.h"

class Wait : public BirdState
{
public:
	Wait();
	~Wait();
	void Enter(Bird* pBird) override;
	void Exit(Bird* pBird) override;
	void Execute(float totalTime, Bird* pBird) override;
	static Wait* GetInstance();
private:
	
};




#endif