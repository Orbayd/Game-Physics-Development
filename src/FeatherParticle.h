#ifndef FEATHER_PARTICLE_H
#define FEATHER_PARTICLE_H

#include "Particle.h"

class FeatherParticle : public Particle
{
public:
	// Create
	FeatherParticle(GameObjectName::Name name, GraphicsObject_Sprite *pSprite, GameSortBucket *pSort);
	FeatherParticle() = delete;
	virtual ~FeatherParticle(){}

	static FeatherParticle *Create(GameObjectName::Name gObjName, ImageName::Name imageName, Rect rect, GameSortBucket *pSort);
	virtual void CreateBody(b2Vec2 center, float scale, float angle, b2Vec2 linVel, float angleVel) override;
	virtual void WorldUpdate(float currentTime) override;
private:

};


#endif