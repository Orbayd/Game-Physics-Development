#include "Block.h"
#include "GameObjectMan.h"
#include "DebugOut.h"
#include "AzulHelper.h"
#include "BlockHealty.h"
Block::Block(GameObjectName::Name name, GraphicsObject_Sprite *pSprite, GameSortBucket *pSort)
	:GameObject2D(name, pSprite)
{
	this->scaleFactor = 1.0f;
	pBlockSound = 0;
	GameObjectMan::Add(this, pSort);
	pBlockState = BlockHealty::GetInstance();
	pBlockState->Enter(this);
	
}
void Block::DeadPhase()
{
	

	

}
Block::~Block()
{

}
void Block::ChangeState(BlockState *pState)
{
	this->pBlockState->Exit(this);
	this->pBlockState = pState;
	this->pBlockState->Enter(this);
}
void Block::goNextPhase()
{
	GraphicsObject_Sprite* pSrite =(GraphicsObject_Sprite*)this->getGraphicsObject();
	pSrite->SetImage((ImageName::Name)((int)pSrite->pImage->name + 1));
}
void Block::WorldUpdate(float currentTime)
{
	AZUL_UNUSED_FLOAT(currentTime);

	// Goal: update the world matrix
	Matrix ScaleF(MatrixScaleType::SCALE, this->scaleFactor, this->scaleFactor, 1.0f);
	Matrix Scale(MatrixScaleType::SCALE, this->scaleX, this->scaleY, 1.0f);
	Matrix Rot(RotType::ROT_Z, this->angle);
	Matrix Trans(MatrixTransType::TRANS, this->posX, this->posY, 0.0f);

	*this->pWorld = ScaleF* Scale * Rot * Trans;

	ApplyDamage();

}
void Block::ApplyDamage()
{
	//Make State Machine
	ImageName::Name iNameNext = static_cast<ImageName::Name>(static_cast<int> (this->iName + 1));
	if (this->damage > 20.0f && this->damage <= 50.0f)
	{
		
		
		pGameSprite->SetImage(iNameNext);
	}
	else if (this->damage > 50.0f && this->damage < 75.0f)
	{
		pGameSprite->SetImage(iNameNext);
		
	}
	else if (this->damage >= 75.0f && this->damage < 100.0f)
	{
		pGameSprite->SetImage(iNameNext);
	}
	else if (this->damage > 100.0f)
	{
		out("---> Death:%x life:%f\n", this->name, this->maxDamage);
		this->deleteMe = true;

		// Add to death list
		GameObjectMan::AddToDeleteList(this);
	}
	

}