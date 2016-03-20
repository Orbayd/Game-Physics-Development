#ifndef BOMB_EMITTER
#define BOMB_EMITTER

#include "ParticleEmitter.h"
#include "GameObjectName.h"
#include "ImageName.h"
#include "Rect.h"
#include "GameSortBucket.h"
#include "Box2D.h"

class BombEmitter : public ParticleEmitter
{
public:
	BombEmitter(GameObjectName::Name gObjName, Rect rect, GameSortBucket *pSort, ImageName::Name imageName0);
	BombEmitter() = delete;

	virtual void Spawn(float maxLifeTime, ImageName::Name imageName, float scale, b2Vec2 linearVel, float angle, float angleVel) override;
	virtual void SpawnMultiple(int num) override;
	
	void SetCenter(b2Vec2 centerPos);


private:
	void privSpawnMultiple(int num, ImageName::Name imageName0);

	b2Vec2 center;


};



#endif