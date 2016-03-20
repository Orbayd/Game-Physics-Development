#ifndef PARTICLE_H
#define PARTICLE_H

#include "GameObject2D.h"
#include "GameSortBucket.h"

class Particle : public GameObject2D
{

public:
	// Create
	Particle(GameObjectName::Name name, GraphicsObject_Sprite *pSprite, GameSortBucket *pSort);

	virtual ~Particle();

	virtual void CreateBody(b2Vec2 center, float scale, float angle, b2Vec2 linVel, float angleVel) = 0;

//	virtual void AddDamage(float normalImpulse) override;
	virtual void WorldUpdate(float currentTime) override;

	float lifeTime;
	float maxLifeTime;
};


#endif