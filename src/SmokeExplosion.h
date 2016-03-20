#ifndef SMOKE_EXPLOSION_H
#define SMOKE_EXPLOSION_H



#include "Particle.h"

class SmokeExplosion : public Particle
{
public:
	// Create
	SmokeExplosion(GameObjectName::Name name, GraphicsObject_Sprite *pSprite, GameSortBucket *pSort);
	SmokeExplosion() = delete;
	virtual ~SmokeExplosion(){}

	static SmokeExplosion *Create(GameObjectName::Name gObjName, ImageName::Name imageName, Rect rect, GameSortBucket *pSort);
	virtual void CreateBody(b2Vec2 center, float scale, float angle, b2Vec2 linVel, float angleVel) override;
	virtual void WorldUpdate(float currentTime) override;
private:
	float animationTime;
};


#endif