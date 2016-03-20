#include "WoodBlock.h"
#include "GameObjectMan.h"
#include "DebugOut.h"
#include "AzulHelper.h"

#include "ChunkEmitter.h"
#include "PixelToMeter.h"
#include "Level.h"

#include "SoundMan.h"
#include "WoodBlockSound.h"
#include "BlockState.h"
WoodBlock::WoodBlock(GameObjectName::Name name, GraphicsObject_Sprite *pSprite, GameSortBucket *pSort)
	:Block(name, pSprite, pSort)
{
	this->pBlockSound = new WoodBlockSoundObj();
	this->maxDamage = 100.0f;
	//GameSortBucket * pSort = (GameSortBucket *)GameObjectMan::Find(GameObjectName::Birds_Sort);
	pEmitter = new ChunkEmitter(GameObjectName::L1_RedBird, Rect(-800.0f, 400.0f, 35.0f, 8.0f), pSort, ImageName::WoodChunk_0, ImageName::WoodChunk_1, ImageName::WoodChunk_2);
}

WoodBlock::~WoodBlock()
{

}

void WoodBlock::WorldUpdate(float currentTime)
{
	AZUL_UNUSED_FLOAT(currentTime);

	// Goal: update the world matrix
	Matrix ScaleF(MatrixScaleType::SCALE, this->scaleFactor, this->scaleFactor, 1.0f);
	Matrix Scale(MatrixScaleType::SCALE, this->scaleX, this->scaleY, 1.0f);
	Matrix Rot(RotType::ROT_Z, this->angle);
	Matrix Trans(MatrixTransType::TRANS, this->posX, this->posY, 0.0f);

	*this->pWorld = ScaleF* Scale * Rot * Trans;

	/*ApplyDamage();*/
	this->pBlockState->Execute(currentTime, this);
	//if (this->damage >= (this->maxDamage - 0.01f))
	//{
	//	out("---> Death:%x damage:%f\n", this->name, this->damage);
	//	//SoundManager::Play("../../data/wood destroyed a1.wav");	
	//	
	//	this->deleteMe = true;
	//	this->pEmitter->SetCenter(b2Vec2((this->posX), (this->posY)));
	//	pBlockSound->Play(SoundType::DEATH);
	//	CreateChunks();
	//	// Add to death list
	//	GameObjectMan::AddToDeleteList(this);
	//}
	//ApplyDamage();

}
void WoodBlock::ApplyDamage()
{
	/*if (this->name == GameObjectName::L1_LeftBlock)
	{
		out("life %f \n", this->life);
	}*/
	//Make State Machine
	if (this->damage >= (this->maxDamage*0.250f - 0.01f) )
	{
		
		pGameSprite->SetImage(ImageName::LongWoodBlock_Minor);
	}
	else if (this->damage >= (this->maxDamage*0.50f - 0.01f))
	{
		
		pGameSprite->SetImage(ImageName::LongWoodBlock_Moderate);

	}
	else if (this->damage >= (this->maxDamage*0.75f - 0.01f))
	{
		
		pGameSprite->SetImage(ImageName::LongWoodBlock_NearDead);
	}
	else if (this->damage >= (this->maxDamage - 0.01f))
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
	//else if (this->damage > 200.0f)
	//{
	//	this->deleteMe = true;
	//	this->pEmitter->SetCenter(b2Vec2((this->posX), (this->posY)));
	//	pBlockSound->Play(SoundType::DEATH);
	//	CreateChunks();
	//	// Add to death list
	//     GameObjectMan::AddToDeleteList(this);
	//}


}
void WoodBlock::CreateChunks()
{
	pEmitter->SpawnMultiple(5);
}
void WoodBlock::DeadPhase()
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