#ifndef TRAIL_PARTICLE_H
#define TRAIL_PARTICLE_H

#include "Particle.h"

class TrailParticle : public Particle
{
public:
	// Create
	TrailParticle(GameObjectName::Name name, GraphicsObject_Sprite *pSprite, GameSortBucket *pSort);
	TrailParticle() = delete;
	virtual ~TrailParticle(){}

	static TrailParticle *Create(GameObjectName::Name gObjName, ImageName::Name imageName, Rect rect, GameSortBucket *pSort);
	virtual void CreateBody(b2Vec2 center, float scale, float angle, b2Vec2 linVel, float angleVel) override;

	virtual void WorldUpdate(float currentTime) override;

private:

};


#endif