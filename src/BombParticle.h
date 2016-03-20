#ifndef BOMB_PARTICLE_H
#define BOMB_PARTICLE_H

#include "Particle.h"

class BombParticle : public Particle
{
public:
	// Create
	BombParticle(GameObjectName::Name name, GraphicsObject_Sprite *pSprite, GameSortBucket *pSort);
	BombParticle() = delete;
	virtual ~BombParticle(){}

	static BombParticle *Create(GameObjectName::Name gObjName, ImageName::Name imageName, Rect rect, GameSortBucket *pSort);
	virtual void CreateBody(b2Vec2 center, float scale, float angle, b2Vec2 linVel, float angleVel) override;
	virtual void WorldUpdate(float currentTime) override;
private:
	b2Vec2 blastCenter;
};


#endif