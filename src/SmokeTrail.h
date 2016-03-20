#ifndef SMOKE_H
#define SMOKE_H
#include "Particle.h"

class GameSortBucket;
class  Smoke : public Particle
{
public:
	Smoke(GameObjectName::Name name, GraphicsObject_Sprite *pSprite, GameSortBucket *pSort);
	virtual ~Smoke();
	Smoke() = delete;
	
	virtual void WorldUpdate(float currentTime)override;
private:
	virtual void CreateBody(b2Vec2 center, float scale, float angle, b2Vec2 linVel, float angleVel) override;
};



#endif
