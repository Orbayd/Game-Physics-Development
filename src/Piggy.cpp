#include "Piggy.h"
#include "GameObjectMan.h"
#include "DebugOut.h"
#include "AzulHelper.h"

#include "TimerMan.h"
#include "OinkEvent.h"
#include "Blink.h"
#include "PigSounds.h"
#include "Simulation.h"

#include "Healty.h"
#include "SmokeEmitter.h"
Piggy::Piggy(GameObjectName::Name name, GraphicsObject_Sprite *pSprite, GameSortBucket *pSort)
	:GameObject2D(name, pSprite)
{
	GameObjectMan::Add(this, pSort);
	
	this->maxDamage = 20.0;
	GameSortBucket *pEffectSort = (GameSortBucket*)GameObjectMan::Find(GameObjectName::Effects_Sort);
	this->pSmokeEmitter = new SmokeEmitter(GameObjectName::L1_RedBird, Rect(800.0f, 400.0f, 35.0f, 35.0f), pEffectSort, ImageName::SmallSmoke);
	
	this->pPiggyState = PiggyHealty::GetInstance();
	pPiggyState->Enter(this);
}

Piggy::~Piggy()
{

}
void Piggy::DeadPhase()
{
	this->pSmokeEmitter->SetCenter(b2Vec2(this->posX, this->posY ));
	this->pSmokeEmitter->SpawnMultiple(5);
}
void Piggy::WorldUpdate(float currentTime)
{
	AZUL_UNUSED_FLOAT(currentTime);

	// Goal: update the world matrix
	Matrix Scale(MatrixScaleType::SCALE, this->scaleX, this->scaleY, 1.0f);
	Matrix Rot(RotType::ROT_Z, this->angle);
	Matrix Trans(MatrixTransType::TRANS, this->posX, this->posY, 0.0f);

	*this->pWorld = Scale * Rot * Trans;
	
	pPiggyState->Execute(Simulation::Instance()->getTotalTime(), this);


}

void Piggy::AddDamage(float normalImpulse)
{

	if (this->pBody->GetType() != b2_staticBody)
	{
		this->damage += normalImpulse;
		this->pendingDamage += normalImpulse;
		//out("(%x)Damage:%f\n", this->getName(), this->damage);
	}

}

void Piggy::ChangeState(PiggyState * pState)
{
	this->pPiggyState->Exit(this);
	this->pPiggyState = pState;
	this->pPiggyState->Enter(this);



}