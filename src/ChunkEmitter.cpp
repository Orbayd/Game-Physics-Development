#include <assert.h>

#include "Particle.h"
#include "ChunkParticle.h"
#include "ChunkEmitter.h"


ChunkEmitter::ChunkEmitter(GameObjectName::Name gObjName, Rect rect, GameSortBucket *pSort, ImageName::Name imageName0, ImageName::Name _imageName1, ImageName::Name _imageName2)
	:ParticleEmitter(gObjName, rect, pSort, imageName0)
{
	this->center = b2Vec2(rect.x, rect.y);
	this->imageName1 = _imageName1;
	this->imageName2 = _imageName2;

}

void ChunkEmitter::SetCenter(b2Vec2 centerPos)
{
	this->center = centerPos;
}

void ChunkEmitter::Spawn(float maxLifeTime, ImageName::Name imageName, float scale, b2Vec2 linearVel, float angle, float angleVel)
{
	// Create a feather
	ChunkParticle *pParticle = ChunkParticle::Create(this->gObjName, imageName, this->rect, this->pSort);
	assert(pParticle);

	// Setup the physics body
	pParticle->CreateBody(this->center, scale, angle, linearVel, angleVel);

	// Setup game object variables
	pParticle->maxLifeTime = maxLifeTime;
}

void ChunkEmitter::SpawnMultiple(int num)
{
	this->privSpawnMultiple(num, this->imageName0);
	this->privSpawnMultiple(num, this->imageName1);
	this->privSpawnMultiple(num, this->imageName2);
}

void ChunkEmitter::privSpawnMultiple(int num, ImageName::Name imageName)
{
	for (int i = 0; i < num; i++)
	{
		float randX = 8.0f*((rand() % 10) / 10.0f - 0.5f);
		float randY = 8.0f*((rand() % 10) / 10.0f - 0.5f);
		float angle = (float)(rand() % 360);
		float life = 1.0f + 1.5f*(rand() % 10) / 10.0f;
		float angleVel = 2.0f*(rand() % 10) / 10.0f - 4.0f;
		float scale = 0.5f*(rand() % 10) / 10.0f + 0.4f;
		this->Spawn(life, imageName, scale, b2Vec2(randX, randY), angle, angleVel);
	}
}
