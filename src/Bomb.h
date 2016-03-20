#ifndef BOMB_H
#define  BOMB_H
#include "BirdAbility.h"
class BombEmitter;
class Bomb : public Ability
{
public:
	Bomb();
	~Bomb();
	 void  Execute(Bird* pBird) override;
	 static Bomb *getInstance();
private:
	
	BombEmitter * pEmitter;
};



#endif