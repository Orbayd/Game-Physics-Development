#ifndef READY_H
#define READY_H
#include "BirdState.h"
#include "Box2D.h"
class Ready : public BirdState
{
public:
	Ready();
	~Ready();
	void Enter(Bird* pBird) override;
	void Exit(Bird* pBird) override;
	void Execute(float totalTime, Bird* pBird) override;
	static Ready* GetInstance();
private:
	b2Vec2 firstPos;
	b2Vec2 lastPos;
};




#endif