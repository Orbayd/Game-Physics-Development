#include <assert.h>

#include "Particle.h"
#include "SmokeParticle.h"
#include "SmokeEmitter.h"


SmokeEmitter::SmokeEmitter(GameObjectName::Name gObjName, Rect rect, GameSortBucket *pSort, ImageName::Name imageName0)
	:ParticleEmitter(gObjName, rect, pSort, imageName0)
{
	this->center = b2Vec2(rect.x, rect.y);

}

void SmokeEmitter::SetCenter(b2Vec2 centerPos)
{
	this->center = centerPos;
}

void SmokeEmitter::Spawn(float maxLifeTime, ImageName::Name imageName, float scale, b2Vec2 linearVel, float angle, float angleVel)
{
	// Create a Smoke
	SmokeParticle *pParticle = SmokeParticle::Create(this->gObjName, imageName, this->rect, this->pSort);
	assert(pParticle);

	// Setup the physics body
	pParticle->CreateBody(this->center, scale, angle, linearVel, angleVel);

	// Setup game object variables
	pParticle->maxLifeTime = maxLifeTime;

	// Order of operations - since we are adding in update, the object needs to be updated
	pParticle->Update(0.0f);
}

void SmokeEmitter::SpawnMultiple(int num)
{
	this->privSpawnMultiple(num, this->imageName0);
}

void SmokeEmitter::privSpawnMultiple(int num, ImageName::Name imageName)
{
	for (int i = 0; i < num; i++)
	{
		float randX = 5.0f*((rand() % 10) / 10.0f - 0.5f);
		float randY = 5.0f*((rand() % 10) / 10.0f - 0.5f);
		float angle = (float)(rand() % 360);
		float life = 1.0f + 1.0f*(rand() % 10) / 10.0f;
		float angleVel = 3.0f*(rand() % 10) / 10.0f - 4.0f;
		float scale = 0.75f*(rand() % 10) / 10.0f + 0.2f;
 		this->Spawn(life, imageName, scale, b2Vec2(randX, randY), angle, angleVel);
	}
}
