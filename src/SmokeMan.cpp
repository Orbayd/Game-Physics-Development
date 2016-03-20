#include "SmokeMan.h"
#include "SmokeFactory.h"
#include "GameObjectMan.h"
#include "Image.h"
#include "Bird.h"
#include "Smoke.h"
#include "DebugOut.h"
SmokeManager::SmokeManager()
{

	

	active = (GameSortBucket *)GameObjectMan::Find(GameObjectName::SmokeBucket_A);
	assert(active);
	passive = (GameSortBucket *)GameObjectMan::Find(GameObjectName::SmokeBucket_B);
	assert(passive);
	SmokePos.set(170.0, 200, 0);
	
}

SmokeManager::~SmokeManager()
{
}
SmokeManager * SmokeManager::getInstance()
{
	static	SmokeManager instance;
	return &instance;
}

void SmokeManager::CreateSmoke(float PosX, float PosY)
{
	SmokeManager * instance = SmokeManager::getInstance();
	
	SmokeFactory::Create(ImageName::Smoke, Rect(PosX, PosY, 10, 10), instance->active);

}

void SmokeManager::Update(float totalTime)
{
	totalTime;
	SmokeManager * instance = SmokeManager::getInstance();
	if (CheckDistance())
	{
		instance->CreateSmoke(instance->SmokePos[X], instance->SmokePos[Y]);
		out("Created Smoke at : <%f> , <%f> \n", instance->SmokePos[X], instance->SmokePos[Y]);
	}
	
	

}
bool SmokeManager::CheckDistance()
{
	SmokeManager * instance = SmokeManager::getInstance();
	assert(instance->active);

	Bird *pBird = (Bird*)GameObjectMan::getBird();
	if (pBird->deleteMe == true)
	{
		//Quick Hack 
		return false;
	}
	Vect BirdPos(pBird->posX, pBird->posY, 0);
	
	float dist = (BirdPos - instance->SmokePos).mag();
	if (dist > 15.0f && BirdPos[x]> instance->SmokePos[x])
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

	GameSortBucket * pTemp = instance->active;
	instance->active = instance->passive;
	instance->passive = pTemp;


}

void SmokeManager::ClearBucket()
{
	SmokeManager * instance = SmokeManager::getInstance();
	assert(instance->active->getChild());

	GameObject2D *pGobj = (GameObject2D *)instance->active->getChild();
	while (pGobj != 0)
	{
		GameObject2D *pGNext = (GameObject2D *)pGobj->getSibling();
		GameObjectMan::Delete(pGobj);
		pGobj = pGNext;
	}
	instance->SmokePos.set(170.0, 200, 0);
	out("Cleared Bucket\n");
}