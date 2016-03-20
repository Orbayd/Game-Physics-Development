#include "WoodPlatform.h"
#include "GameObjectMan.h"
#include "AzulHelper.h"
WoodPlatform::WoodPlatform(GameObjectName::Name name, GraphicsObject_Sprite *pSprite, GameSortBucket *pSort)
	:GameObject2D(name, pSprite)
{
	this->scaleFactor = 1.0f;
	GameObjectMan::Add(this, pSort);

}
WoodPlatform::~WoodPlatform()
{
}

void WoodPlatform::WorldUpdate(float currentTime)
{
	AZUL_UNUSED_FLOAT(currentTime);

	// Goal: update the world matrix
	Matrix ScaleF(MatrixScaleType::SCALE, this->scaleFactor, this->scaleFactor, 1.0f);
	Matrix Scale(MatrixScaleType::SCALE, this->scaleX, this->scaleY, 1.0f);
	Matrix Rot(RotType::ROT_Z, this->angle);
	Matrix Trans(MatrixTransType::TRANS, this->posX, this->posY, 0.0f);

	*this->pWorld = ScaleF* Scale * Rot * Trans;


}