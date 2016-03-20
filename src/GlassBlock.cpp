#include "GlassBlock.h"
#include "GameObjectMan.h"
#include "DebugOut.h"
#include "AzulHelper.h"
#include "BlockState.h"
#include "ChunkEmitter.h"
#include "GlassBlockSound.h"
GlassBlock::GlassBlock(GameObjectName::Name name, GraphicsObject_Sprite *pSprite, GameSortBucket *pSort)
	:Block(name, pSprite, pSort)
{
	this->scaleFactor = 1.0f;
	//GameObjectMan::Add(this, pSort);
	this->pBlockSound = new GlassBlockSoundObj();
	this->maxDamage = 50;
	pEmitter = new ChunkEmitter(GameObjectName::L1_RedBird, Rect(800.0f, 400.0f, 35.0f, 8.0f), pSort, ImageName::GlassChunk_0, ImageName::GlassChunk_1, ImageName::GlassChunk_2);
}

GlassBlock::~GlassBlock()
{

}

void GlassBlock::WorldUpdate(float currentTime)
{
	AZUL_UNUSED_FLOAT(currentTime);

	// Goal: update the world matrix
	Matrix ScaleF(MatrixScaleType::SCALE, this->scaleFactor, this->scaleFactor, 1.0f);
	Matrix Scale(MatrixScaleType::SCALE, this->scaleX, this->scaleY, 1.0f);
	Matrix Rot(RotType::ROT_Z, this->angle);
	Matrix Trans(MatrixTransType::TRANS, this->posX, this->posY, 0.0f);

	*this->pWorld = ScaleF* Scale * Rot * Trans;
	this->pBlockState->Execute(currentTime, this);
	//ApplyDamage();

}
void GlassBlock::ApplyDamage()
{
	//Make State Machine
	if (this->damage > 20.0f && this->damage <= 40.0f)
	{

		pGameSprite->SetImage(ImageName::GlassBlock_Minor);
	}
	else if (this->damage > 40.0f && this->damage < 80.0f)
	{
		pGameSprite->SetImage(ImageName::GlassBlock_Moderate);

	}
	else if (this->damage >= 80.0f && this->damage < 100.0f)
	{
		pGameSprite->SetImage(ImageName::GlassBlock_NearDead);
	}
	else if (this->damage > 100.0f)
	{
		out("---> Death:%x life:%f\n", this->name, this->maxDamage);
		this->deleteMe = true;

		// Add to death list
		GameObjectMan::AddToDeleteList(this);
	}


}
void GlassBlock::CreateChunks()
{
	pEmitter->SpawnMultiple(5);
}
void GlassBlock::DeadPhase()
{
	out("---> Death:%x damage:%f\n", this->name, this->damage);
	//SoundManager::Play("../../data/wood destroyed a1.wav");	

	this->deleteMe = true;
	this->pEmitter->SetCenter(b2Vec2((this->posX), (this->posY)));
	pBlockSound->Play(SoundType::DEATH);
	CreateChunks();
	// Add to death list
	GameObjectMan::AddToDeleteList(this);
}