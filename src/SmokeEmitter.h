#ifndef SMOKE_EMITTER
#define SMOKE_EMITTER

#include "ParticleEmitter.h"
#include "GameObjectName.h"
#include "ImageName.h"
#include "Rect.h"
#include "GameSortBucket.h"
#include "Box2D.h"

class SmokeEmitter : public ParticleEmitter
{
public:
	SmokeEmitter(GameObjectName::Name gObjName, Rect rect, GameSortBucket *pSort, ImageName::Name imageName0);
	SmokeEmitter() = delete;

	virtual void Spawn(float maxLifeTime, ImageName::Name imageName, float scale, b2Vec2 linearVel, float angle, float angleVel) override;
	virtual void SpawnMultiple(int num) override;

	void SetCenter(b2Vec2 centerPos);


private:
	void privSpawnMultiple(int num, ImageName::Name imageName0);

	b2Vec2 center;


};



#endif