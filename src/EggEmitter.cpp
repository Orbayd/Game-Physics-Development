#include <assert.h>

#include "Particle.h"
#include "Egg.h"
#include "EggEmitter.h"


EggEmitter::EggEmitter(GameObjectName::Name gObjName, Rect rect, GameSortBucket *pSort, ImageName::Name imageName0)
	:ParticleEmitter(gObjName, rect, pSort, imageName0)
{
	this->center = b2Vec2(rect.x, rect.y);
}

void EggEmitter::SetCenter(b2Vec2 centerPos)
{
	this->center = centerPos;
}

void EggEmitter::Spawn(float maxLifeTime, ImageName::Name imageName, float scale, b2Vec2 linearVel, float angle, float angleVel)
{
	// Create a feather
	Egg *pParticle = Egg::Create(this->gObjName, imageName, this->rect, this->pSort);
	assert(pParticle);

	// Setup the physics body
	pParticle->CreateBody(this->center, scale, angle, linearVel, angleVel);

	// Setup game object variables
	pParticle->maxLifeTime = maxLifeTime;
}

void EggEmitter::SpawnMultiple(int num)
{
	num;
}

void EggEmitter::privSpawnMultiple(int num, ImageName::Name imageName)
{
	num; imageName;
}
