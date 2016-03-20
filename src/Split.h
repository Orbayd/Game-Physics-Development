#ifndef SPLIT_H
#define  SPLIT_H
#include "BirdAbility.h"
class BombEmitter;
class Split : public Ability
{
public:
	Split();
	virtual ~Split();
	void  Execute(Bird* pBird) override;
	static Split *getInstance();
private:


};



#endif