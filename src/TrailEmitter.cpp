#include <assert.h>

#include "Particle.h"
#include "TrailParticle.h"
#include "TrailEmitter.h"

#include "ImageMan.h"
TrailEmitter::TrailEmitter(GameObjectName::Name gObjName, Rect rect, GameSortBucket *pSort, ImageName::Name _imageName0, ImageName::Name _imageName1, ImageName::Name _imageName2)
	:ParticleEmitter(gObjName, rect, pSort, _imageName0)
{
	this->center = b2Vec2(rect.x, rect.y);
	this->count = 0;

	this->imageName1 = _imageName1;
	this->imageName2 = _imageName2;

}

void TrailEmitter::SetCenter(b2Vec2 centerPos )
{
	this->center = centerPos;
}

void TrailEmitter::Spawn(float maxLifeTime, ImageName::Name imageName, float scale, b2Vec2 linearVel, float angle, float angleVel)
{
	// Create a Smoke
	scale; linearVel; angle; angleVel;
	Rect a;
 	a.x = this->center.x;
	a.y = this->center.y;
	a.width = ImageMan::find(imageName)->imageRect.width * scale;
	a.height = a.width = ImageMan::find(imageName)->imageRect.height * scale ;
 	
	TrailParticle *pParticle = TrailParticle::Create(this->gObjName, imageName,a, this->pSort);
	assert(pParticle);

	// Setup the physics body
	//pParticle->CreateBody(this->center, scale, angle, linearVel, angleVel);

	// Setup game object variables
	pParticle->maxLifeTime = maxLifeTime;

	// Order of operations - since we are adding in update, the object needs to be updated
	pParticle->Update(0.0f);
}

void TrailEmitter::SpawnMultiple(int num)
{
	num;
	//this->privSpawnMultiple(num, this->imageName0);
}

void TrailEmitter::Spawn(b2Vec2 center, GameSortBucket * _pSort)
{
	this->SetCenter(center);
	this->pSort = _pSort;
	if (count % 3 == 0)
	{
 		this->Spawn(100000.0f, imageName0, 0.8f, b2Vec2(0.0f, 0.0f), 0.0f, 0.0f);
	}
	else if (count % 3 == 1)
	{
		this->Spawn(100000.0f, imageName1, 0.8f, b2Vec2(0.0f, 0.0f), 0.0f, 0.0f);
	}
	else
	{
		this->Spawn(100000.0f, imageName2, 0.8f, b2Vec2(0.0f, 0.0f), 0.0f, 0.0f);
	}

	count++;
	count = count % 3;
}

void TrailEmitter::Spawn(ImageName::Name imageName, b2Vec2 center, GameSortBucket *_pSort, float scale)
{
	this->SetCenter(center);
	this->pSort = _pSort;

	this->Spawn(100000.0f, imageName, scale, b2Vec2(0.0f, 0.0f), 0.0f, 0.0f);
}

