#include "SmokeTrail.h"
#include "AzulHelper.h"
#include "GameObjectMan.h"
Smoke::Smoke(GameObjectName::Name _name, GraphicsObject_Sprite *_pSprite, GameSortBucket *pSort) : Particle(_name, _pSprite, pSort)
{
	//GameObjectMan::Add(this, pSort);
}

Smoke::~Smoke()
{
}
void Smoke::WorldUpdate(float currentTime)
{
	AZUL_UNUSED_FLOAT(currentTime);

	// Goal: update the world matrix
	Matrix Scale(MatrixScaleType::SCALE, this->scaleX, this->scaleY, 1.0f);
	Matrix Rot(RotType::ROT_Z, this->angle);
	Matrix Trans(MatrixTransType::TRANS, this->posX, this->posY, 0.0f);

	*this->pWorld = Scale * Rot * Trans;
}
void Smoke::CreateBody(b2Vec2 center, float scale, float angle, b2Vec2 linVel, float angleVel)
{
	center;
	linVel;
	AZUL_UNUSED_FLOAT(scale);
	AZUL_UNUSED_FLOAT(angle);
	AZUL_UNUSED_FLOAT(angleVel);
}