#ifndef EGG_EMITTER
#define EGG_EMITTER

#include "ParticleEmitter.h"
#include "GameObjectName.h"
#include "ImageName.h"
#include "Rect.h"
#include "GameSortBucket.h"
#include "Box2D.h"

class EggEmitter : public ParticleEmitter
{
public:
	EggEmitter(GameObjectName::Name gObjName, Rect rect, GameSortBucket *pSort, ImageName::Name imageName0);
	EggEmitter() = delete;
	virtual void Spawn(float maxLifeTime, ImageName::Name imageName, float scale, b2Vec2 linearVel, float angle, float angleVel) override;
	void SetCenter(b2Vec2 centerPos);


private:
	void privSpawnMultiple(int num, ImageName::Name imageName0);
	virtual void SpawnMultiple(int num) override;
	b2Vec2 center;


};



#endif