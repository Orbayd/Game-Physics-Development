#ifndef TRAIL_EMITTER
#define TRAIL_EMITTER

#include "ParticleEmitter.h"
#include "GameObjectName.h"
#include "ImageName.h"
#include "Rect.h"
#include "GameSortBucket.h"
#include "Box2D.h"

class TrailEmitter : public ParticleEmitter
{
public:
	TrailEmitter(GameObjectName::Name gObjName, Rect rect, GameSortBucket *pSort, ImageName::Name imageName0, ImageName::Name imageName1, ImageName::Name imageName2);
	TrailEmitter() = delete;

	
	virtual void SpawnMultiple(int num) override;
	void Spawn(b2Vec2 center,GameSortBucket *pSort);
	void Spawn(ImageName::Name imageName, b2Vec2 center, GameSortBucket *pSort,float scale);
	void SetCenter(b2Vec2 centerPos);
	

private:
	void privSpawnMultiple(int num, ImageName::Name imageName0);
	virtual void Spawn(float maxLifeTime, ImageName::Name imageName, float scale, b2Vec2 linearVel, float angle, float angleVel) override;
	ImageName::Name imageName1;
	ImageName::Name imageName2;

	b2Vec2 center;
	int count;

};



#endif