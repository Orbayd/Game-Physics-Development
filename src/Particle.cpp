#include "Particle.h"
#include "GameObjectMan.h"
#include "DebugOut.h"
#include "AzulHelper.h"
#include "Simulation.h"
#include "PixelToMeter.h"
#include "World.h"

Particle::Particle(GameObjectName::Name name, GraphicsObject_Sprite *pSprite, GameSortBucket *pSort)
	:GameObject2D(name, pSprite)
{
	GameObjectMan::Add(this, pSort);
	this->maxLifeTime = 0.0f;
	this->lifeTime = 0.0f;
}

Particle::~Particle()
{

}

//void Particle::AddDamage(float normalImpulse)
//{
//	normalImpulse;
//	
//}

void Particle::WorldUpdate(float currentTime)
{
	AZUL_UNUSED_FLOAT(currentTime);

	// Goal: update the world matrix
	Matrix Scale(MatrixScaleType::SCALE, this->scaleX, this->scaleY, 1.0f);
	Matrix Rot(RotType::ROT_Z, this->angle);
	Matrix Trans(MatrixTransType::TRANS, this->posX, this->posY, 0.0f);

	*this->pWorld = Scale * Rot * Trans;

	float timeInSec = Simulation::Instance()->getTimeStep();
	this->lifeTime += timeInSec;

	// add schrink
	//if (timeInSec > 0.0f)
	//{
	//	this->scaleX *= 0.99f;
	//	this->scaleY *= 0.99f;
	//}

//	this->pendingDamage = this->damage;

	// test with a small delta
	if (this->lifeTime >= maxLifeTime)
	{
		this->deleteMe = true;
		// Add to death list
		GameObjectMan::AddToDeleteList(this);
	}
}

