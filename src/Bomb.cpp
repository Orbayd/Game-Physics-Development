#include "Bomb.h"
#include "Bird.h"
#include "BombEmitter.h"
#include "GameObjectMan.h"
#include "PixelToMeter.h"
#include "TimerMan.h"
#include "SoundMan.h"
#include "SmokeTrailMan.h"
Bomb::Bomb()
{
	GameSortBucket *pSortParticles = (GameSortBucket*)GameObjectMan::Find(GameObjectName::Effects_Sort);
	pEmitter = new BombEmitter(GameObjectName::Bomb_Particle, Rect(400.0f, 500.0f, 10.0f, 10.0f), pSortParticles, ImageName::Bang);
	
}

Bomb::~Bomb()
{
}

void Bomb::Execute(Bird * pbird)
{
	pbird;
	//pEmitter->spawnBomb(5.0f, b2Vec2((pbird->posX), (pbird->posY)));
	//pEmitter->spawnBomb(5.0f, pbird->pBody->GetTransform().p);
	this->pEmitter->SetCenter(b2Vec2(pbird->posX, pbird->posY));
	pEmitter->SpawnMultiple(10);

	
	pbird->deleteMe = true;
	pbird->pBody->SetActive(false);
	SoundManager::Play("../../data/bird destroyed.wav");
	GameObjectMan::AddToDeleteList(pbird);
	SmokeManager::AddSmoke(pbird);
}

Bomb* Bomb::getInstance()
{
	static Bomb instance;
	return &instance;


}