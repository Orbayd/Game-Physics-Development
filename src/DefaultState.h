#ifndef DEFAULT_STATE_H
#define DEFAULT_STATE_H
#include "BirdState.h"

class DefaultState : public BirdState
{
public:
	DefaultState();
	~DefaultState();
	void Enter(Bird* pBird) override;
	void Exit(Bird* pBird) override;
	void Execute(float totalTime, Bird* pBird) override;
	static DefaultState* GetInstance();
private:

};




#endif