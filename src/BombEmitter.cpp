#include <assert.h>

#include "Particle.h"
#include "BombParticle.h"
#include "BombEmitter.h"

#include "SmokeExplosion.h"
#include  "GameObjectMan.h"
BombEmitter::BombEmitter(GameObjectName::Name gObjName, Rect rect, GameSortBucket *pSort, ImageName::Name imageName0)
	:ParticleEmitter(gObjName, rect, pSort, imageName0)
{
	this->center = b2Vec2(rect.x, rect.y);
}

void BombEmitter::SetCenter(b2Vec2 centerPos)
{
	this->center = centerPos;
}

void BombEmitter::Spawn(float maxLifeTime, ImageName::Name imageName, float scale, b2Vec2 linearVel, float angle, float angleVel)
{
	// Create a feather
	BombParticle *pParticle = BombParticle::Create(this->gObjName, imageName, this->rect, this->pSort);
	assert(pParticle);

	// Setup the physics body
	pParticle->CreateBody(this->center, scale, angle, linearVel, angleVel);

	// Setup game object variables
	pParticle->maxLifeTime = maxLifeTime;
}

void BombEmitter::SpawnMultiple(int num)
{
	this->privSpawnMultiple(num, this->imageName0);
	
	GameSortBucket *pSort = (GameSortBucket*)GameObjectMan::Find(GameObjectName::Effects_Sort);
	SmokeExplosion::Create(GameObjectName::Smoke, ImageName::SmokeExplosion_0, Rect(center.x, center.y,81,74), pSort);

}

void BombEmitter::privSpawnMultiple(int num, ImageName::Name imageName)
{
	float strength = 50.0f;

	for (int i = 0; i < num; i++)
	{
		float angle = (i / (float)num) * MATH_2PI;
		b2Vec2 rayDir(sinf(angle) * strength, cosf(angle) * strength);

		float life = 5.0f;
		float angleVel = 0.0f;
		float scale = 1.0f;
		this->Spawn(life, imageName, scale, rayDir, 0.0f, angleVel);
	}
}
