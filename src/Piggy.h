#ifndef PIGGY_H
#define PIGGY_H

#include "GameObject2D.h"
#include "GameSortBucket.h"
class PiggyState;
class SmokeEmitter;
class Piggy : public GameObject2D
{
public:
	// Create
	Piggy(GameObjectName::Name name, GraphicsObject_Sprite *pSprite, GameSortBucket *pSort);

	virtual void WorldUpdate(float currentTime) override;
	virtual void AddDamage(float damage)override;
	~Piggy();
	float scaleFactor;
	void DeadPhase();
	void ChangeState(PiggyState * pstate);
private:
	PiggyState *pPiggyState;
	SmokeEmitter * pSmokeEmitter;
	Piggy();

};















#endif