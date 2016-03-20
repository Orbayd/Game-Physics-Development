#ifndef SMOKE_PARTICLE_H
#define SMOKE_PARTICLE_H

#include "Particle.h"

class SmokeParticle : public Particle
{
public:
	// Create
	SmokeParticle(GameObjectName::Name name, GraphicsObject_Sprite *pSprite, GameSortBucket *pSort);
	SmokeParticle() = delete;
	virtual ~SmokeParticle(){}
	virtual void WorldUpdate(float currentTime) override;
	static SmokeParticle *Create(GameObjectName::Name gObjName, ImageName::Name imageName, Rect rect, GameSortBucket *pSort);
	virtual void CreateBody(b2Vec2 center, float scale, float angle, b2Vec2 linVel, float angleVel) override;

private:

};


#endif