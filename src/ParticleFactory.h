#ifndef PARTICLE_FACTORY_H
#define PARTICLE_FACTORY_H

#include "GameObjectName.h"
#include "ImageName.h"
#include "Rect.h"
#include "GameSortBucket.h"
#include "Particle.h"
#include "BombParticle.h"

class ParticleFactory
{
public:
	static BombParticle *CreateBomb(GameObjectName::Name gObjName, ImageName::Name imageName, Rect rect, GameSortBucket *pSort, b2BodyType type,
		b2Vec2 center, b2Vec2 linVel, float density);
	
	static Particle *CreateChunks(GameObjectName::Name gObjName, ImageName::Name imageName, Rect rect, GameSortBucket *pSort, b2BodyType type,
		b2Vec2 center, b2Vec2 linVel, float density,float angle);


};


#endif