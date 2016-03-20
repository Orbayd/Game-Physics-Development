#ifndef DROOPEGG_H
#define DROOPEGG_H
#include "BirdAbility.h"
class EggEmitter;
class DropEgg : public Ability
{
public:
	DropEgg();
	virtual ~DropEgg();
	void  Execute(Bird* pBird) override;
	static DropEgg *getInstance();
private:
	EggEmitter * pEmitter;

};



#endif