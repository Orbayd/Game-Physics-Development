#ifndef BOOMERANG
#define BOOMERANG
#include "BirdAbility.h"

class Boomerang : public Ability
{
public:
	Boomerang();
	virtual ~Boomerang();
	void  Execute(Bird* pBird) override;
	static Boomerang *getInstance();
private:


};



#endif