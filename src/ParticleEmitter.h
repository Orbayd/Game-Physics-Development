#ifndef PARTICLE_EMITTER
#define PARTICLE_EMITTER

#include "GameObjectName.h"
#include "ImageName.h"
#include "Rect.h"
#include "GameSortBucket.h"
#include "Box2D.h"

class ParticleEmitter
{
public:
	ParticleEmitter(GameObjectName::Name gObjName, Rect rect, GameSortBucket *pSort, ImageName::Name imageName0);
	ParticleEmitter() = delete;

	virtual void Spawn(float maxLifeTime, ImageName::Name imageName, float scale, b2Vec2 linearVel, float angle, float angleVel) = 0;
	virtual void SpawnMultiple(int num) = 0;

protected:
	GameObjectName::Name gObjName;
	
	ImageName::Name imageName0;


	Rect rect;
	GameSortBucket *pSort;
};



#endif