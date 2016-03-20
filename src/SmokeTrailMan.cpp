#include "SmokeTrailMan.h"
#include "TrailEmitter.h"
#include "GameObjectMan.h"
#include "Image.h"
#include "Bird.h"
#include "SmokeTrail.h"
#include "DebugOut.h"
#include "TrailEmitter.h"
#include "PixelToMeter.h"
#include "SmokeFactory.h"
SmokeManager::SmokeManager()
{

	

	active = (GameSortBucket *)GameObjectMan::Find(GameObjectName::SmokeBucket_A);
	assert(active);
	passive = (GameSortBucket *)GameObjectMan::Find(GameObjectName::SmokeBucket_B);
	assert(passive);
	activeParticleSmoke = (GameSortBucket *)GameObjectMan::Find(GameObjectName::SmokeBucket_A);
	passiveParticleSmoke = (GameSortBucket *)GameObjectMan::Find(GameObjectName::SmokeBucket_B);
	SmokePos.set(0, 0, 0);
	
	
}

SmokeManager::~SmokeManager()
{
}
SmokeManager * SmokeManager::getInstance()
{
	static	SmokeManager instance;
	return &instance;
}

void SmokeManager::CreateSmoke(float PosX, float PosY ,Bird *pBird)
{
	SmokeManager * instance = SmokeManager::getInstance();
	pBird->pTrailEmitter->Spawn(b2Vec2((PosX), (PosY)), instance->active);

	//SmokeFactory::Create(ImageName::Smoke, Rect(PosX, PosY, 10, 10), instance->active);
   
}

void SmokeManager::Update(float totalTime,Bird *pBird)
{
	totalTime;
	SmokeManager * instance = SmokeManager::getInstance();
	if (CheckDistance(pBird))
	{
		instance->CreateSmoke(instance->SmokePos[X], instance->SmokePos[Y],pBird);
		
	}
}
void SmokeManager::UpdateP(float totalTime, Bird *pBird)
{
	totalTime;
	SmokeManager * instance = SmokeManager::getInstance();
	if (CheckDistance(pBird))
	{
		instance->CreateSmoke(instance->SmokePos[X], instance->SmokePos[Y], pBird);

	}
}
void SmokeManager::CreateSmokeP(float PosX, float PosY, Bird *pBird)
{
	SmokeManager * instance = SmokeManager::getInstance();
	pBird->pTrailEmitter->Spawn(b2Vec2((PosX), (PosY)), instance->activeParticleSmoke);

	//SmokeFactory::Create(ImageName::Smoke, Rect(PosX, PosY, 10, 10), instance->active);

}

bool SmokeManager::CheckDistance(Bird *pBird)
{
	SmokeManager * instance = SmokeManager::getInstance();
	assert(instance->active);

	
	if (pBird->deleteMe == true)
	{
		//Quick Hack 
		return false;
	}
	Vect BirdPos(pBird->posX, pBird->posY, 0);
	
	float dist = (BirdPos - instance->SmokePos).mag();
	if (dist > 25.0f )
	{
		instance->SmokePos = BirdPos;
		return true;
	}
	else
	{
		return false;
	}

}
void SmokeManager::SwitchBuckets()
{
	SmokeManager * instance = SmokeManager::getInstance();
	
 	if (instance->active->getNumChildren()>0 && instance->passive->getNumChildren()>0)
	{
		ClearBucket();
	}

	GameSortBucket * pTemp = instance->active;
	instance->active = instance->passive;
	instance->passive = pTemp;
	
	pTemp = instance->activeParticleSmoke;
	instance->activeParticleSmoke = instance->passiveParticleSmoke;
	instance->passiveParticleSmoke = pTemp;

	instance->SmokePos.set(0.0, 0.0, 0.0);




}

void SmokeManager::ClearBucket()
{
	SmokeManager * instance = SmokeManager::getInstance();
	assert(instance->passive->getChild());

	GameObject2D *pGobj = (GameObject2D *)instance->passive->getChild();
	while (pGobj != 0)
	{
		GameObject2D *pGNext = (GameObject2D *)pGobj->getSibling();
		GameObjectMan::Delete(pGobj);
		pGobj = pGNext;
	}

	//pGobj = (GameObject2D *)instance->passiveParticleSmoke->getChild();
	//while (pGobj != 0)
	//{
	//	GameObject2D *pGNext = (GameObject2D *)pGobj->getSibling();
	//	GameObjectMan::Delete(pGobj);
	//	pGobj = pGNext;
	//}

	instance->SmokePos.set(0.0, 0.0, 0);
	out("Cleared Bucket\n");
}
void SmokeManager::AddSmoke(Bird *pBird)
{
	SmokeManager * instance = SmokeManager::getInstance();
	if (pBird == 0)
	{
		//Quick Hack 
		return;
	}
	
	pBird->pTrailEmitter->Spawn(ImageName::SmallSmoke, b2Vec2(pBird->posX, pBird->posY), instance->activeParticleSmoke, 1.0);
	

}