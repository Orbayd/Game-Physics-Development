#ifndef CHUNK_EMITTER
#define CHUNK_EMITTER

#include "ParticleEmitter.h"
#include "GameObjectName.h"
#include "ImageName.h"
#include "Rect.h"
#include "GameSortBucket.h"
#include "Box2D.h"

class ChunkEmitter : public ParticleEmitter
{
public:
	ChunkEmitter(GameObjectName::Name gObjName, Rect rect, GameSortBucket *pSort, ImageName::Name imageName0, ImageName::Name imageName1, ImageName::Name imageName2);
	ChunkEmitter() = delete;

	virtual void Spawn(float maxLifeTime, ImageName::Name imageName, float scale, b2Vec2 linearVel, float angle, float angleVel) override;
	virtual void SpawnMultiple(int num) override;

	void SetCenter(b2Vec2 centerPos);


private:
	void privSpawnMultiple(int num, ImageName::Name imageName0);

	b2Vec2 center;
	ImageName::Name imageName1;
	ImageName::Name imageName2;

};



#endif