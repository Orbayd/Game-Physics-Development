#ifndef SPEEDUP_H
#define  SPEEDUP_H
#include "BirdAbility.h"

class SpeedUp : public Ability
{
public:
	SpeedUp();
	virtual ~SpeedUp();
	void  Execute(Bird* pBird) override;
	static SpeedUp *getInstance();
private:

	
};



#endif