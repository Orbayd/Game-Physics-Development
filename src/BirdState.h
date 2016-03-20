#ifndef BIRD_STATE_H
#define BIRD_STATE_H
class Bird;
class BirdState
{
public:
	
	
	virtual void Enter(Bird* pBird) = 0;
	virtual void Execute(float totalTime, Bird * pBird) = 0;
	virtual void Exit(Bird* pBird) = 0;

private:
	
};















#endif