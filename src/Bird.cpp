#include "Bird.h"
#include "GameObjectMan.h"
#include "DebugOut.h"
#include "AzulHelper.h"
#include "RubberBand.h"
//Last Addition
#include "SmokeTrailMan.h"

#include "Wait.h"
#include "Flying.h"
#include "Dead.h"
#include "InputMan.h"
#include "FeatherEmitter.h"
#include "SmokeEmitter.h"
#include "TrailEmitter.h"
//Lsted Add
#include "Blink.h"
#include "Jump.h"
#include "ImageMan.h"
#include "Simulation.h"

#include "irrKlang.h"
#include "Warcry.h"
#include "SoundMan.h"


Bird::Bird(GameObjectName::Name name, GraphicsObject_Sprite *pSprite, GameSortBucket *pSort)
	:GameObject2D(name, pSprite)
{
	GameObjectMan::Add(this, pSort);
	this->maxDamage = 1000.0f;
	GameSortBucket *pEffectSort=(GameSortBucket*)GameObjectMan::Find(GameObjectName::Effects_Sort);
	this->pFeatherEmitter = new FeatherEmitter(GameObjectName::L1_RedBird, Rect(800.0f, 400.0f, 40.0f, 120.0f),
		pEffectSort, ImageName::RedFeather, ImageName::OrangeFeather, ImageName::BrownFeather);
	this->pSmokeEmitter = new SmokeEmitter(GameObjectName::L1_RedBird, Rect(800.0f, 400.0f, 35.0f, 35.0f), pEffectSort, ImageName::SmallSmoke);
	this->featherFlag = false;

	GameSortBucket *pTrailSort = (GameSortBucket*)GameObjectMan::Find(GameObjectName::Effects_Sort);
	pTrailEmitter = new TrailEmitter(GameObjectName::SmokeParticle, Rect(800.0f, 800.0f, 30.0f, 30.0f),
		pTrailSort, ImageName::SmallSmoke1, ImageName::SmallSmoke2, ImageName::SmallSmoke3);
	
}

Bird::~Bird()
{
	
}

void Bird::WorldUpdate(float currentTime)
{
	AZUL_UNUSED_FLOAT(currentTime);

	// Goal: update the world matrix
	Matrix Scale(MatrixScaleType::SCALE, this->scaleX, this->scaleY, 1.0f);
	Matrix Rot(RotType::ROT_Z, this->angle);
	Matrix Trans(MatrixTransType::TRANS, this->posX, this->posY, 0.0f);

	*this->pWorld = Scale * Rot * Trans;

	
	this->pbirdState->Execute(currentTime,this);
	if (this->featherFlag == true)
	{
		this->SpawnFeathers();
	}
	
}
void Bird::ChangeState(BirdState* _pbirdState)
{
	this->pbirdState->Exit(this);
	this->pbirdState = _pbirdState;
	this->pbirdState->Enter(this);
}


void Bird::ExecuteAbility()
{
	this->pAbility->Execute(this);
}

void Bird::AddJumpEvent()
{
	std::srand((unsigned int)Simulation::Instance()->getTotalTime()); // use current time as seed for random generator
	int random_Time = std::rand() % 8;
	Jump *pJump = new Jump(this, this->posY + 0.0f, this->posY, 0.0f, 0.0f);
	TimerMan::AddEvent(Simulation::Instance()->getTotalTime() + random_Time, pJump);
	
	
   random_Time = std::rand() % 5;
	WarCry * pWarcry = new WarCry(this);
	TimerMan::AddEvent(Simulation::Instance()->getTotalTime() + random_Time, pWarcry);
}
void Bird::LostAbility()
{
	this->pAbility = NoAbility::getInstance();
	
}
void Bird::DeadPhase()
{

	TimerMan::CleanObjectEvents(this);
	this->deleteMe = true;
	this->pBody->SetActive(false);
	SoundManager::Play("../../data/bird destroyed.wav");
	GameObjectMan::AddToDeleteList(this);



}

void Bird::SpawnFeathers()
{
	((FeatherEmitter*)this->pFeatherEmitter)->SetCenter(b2Vec2(this->posX, this->posY));
	((SmokeEmitter*)this->pSmokeEmitter)->SetCenter(b2Vec2(this->posX, this->posY));
	for (int i = 0; i < 3; i++)
	{
		this->pFeatherEmitter->SpawnMultiple(1);
		this->pSmokeEmitter->SpawnMultiple(1);
	}
	featherFlag = false;
}
void Bird::AddDamage(float normImpulse)
{
	if (normImpulse > 20.0f)
	{
		this->featherFlag = true;
	}

}
BirdState * Bird::getBirdState()
{
	return this->pbirdState;
}


