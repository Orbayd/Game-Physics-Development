#ifndef DEAD_H
#define DEAD_H
#include "BirdState.h"

class Dead : public BirdState
{
public:
	Dead();
	~Dead();
	void Enter(Bird* pBird) override;
	void Exit(Bird* pBird) override;
	void Execute(float totalTime, Bird* pBird) override;
	static Dead* GetInstance();
private:

};




#endif