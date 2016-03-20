#include "StoneBlock.h"
#include "GameObjectMan.h"
#include "DebugOut.h"
#include "AzulHelper.h"
#include "World.h"
#include "PixelToMeter.h"
#include "BlockState.h"
#include "ChunkEmitter.h"
#include "StoneBlockSound.h"
StoneBlock::StoneBlock(GameObjectName::Name name, GraphicsObject_Sprite *pSprite, GameSortBucket *pSort)
	:Block(name, pSprite, pSort)
{
	//this->scaleFactor = 1.0f;
	//GameObjectMan::Add(this, pSort);
	this->pBlockSound = new StoneBlockSoundObj();
	this->maxDamage = 200.0f;
	pEmitter = new ChunkEmitter(GameObjectName::L1_RedBird, Rect(-800.0f, 400.0f, 35.0f, 8.0f), pSort, ImageName::StoneChunk_0, ImageName::StoneChunk_1, ImageName::StoneChunk_2);
}

StoneBlock::~StoneBlock()
{

}

void StoneBlock::WorldUpdate(float currentTime)
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
void StoneBlock::ApplyDamage()
{
	//Make State Machine
	if (this->damage > 100 && this->damage <= 200.0f)
	{

		pGameSprite->SetImage(ImageName::StoneBlock_Minor);
	}
	else if (this->damage > 200.0f && this->damage < 300.0f)
	{
		pGameSprite->SetImage(ImageName::StoneBlock_Moderate);

	}
	else if (this->damage >= 300.0f && this->damage < 400.0f)
	{
		pGameSprite->SetImage(ImageName::StoneBlock_NearDead);
	}
	else if (this->damage > 400.0f)
	{
		out("---> Death:%x life:%f\n", this->name, this->maxDamage);
		this->deleteMe = true;

		// Add to death list
		GameObjectMan::AddToDeleteList(this);
	}


}

StoneBlock * StoneBlock::Create(GameObjectName::Name gObjName, ImageName::Name imageName, Rect rect,float _angle, b2BodyType type)
{
	GameObject *pObj = GameObjectMan::Find(GameObjectName::Blocks_Sort);
	// input validation
	assert(pObj);
	GameSortBucket *pSort = (GameSortBucket *)pObj;

	GraphicsObject_Sprite *pSprite = new GraphicsObject_Sprite(imageName, rect);

	StoneBlock *pBlock = new StoneBlock(gObjName, pSprite, pSort);

	pBlock->angle = _angle;



	b2BodyDef BodyDef;
	BodyDef.type = type;
	BodyDef.position.Set(PixelToMeter(pBlock->posX* pBlock->scaleFactor), PixelToMeter(pBlock->posY*pBlock->scaleFactor));
	BodyDef.angle = pBlock->angle;
	BodyDef.angularDamping = 2.5f;
	/*BodyDef.linearDamping = 5.0f;*/

	// Shape
	b2PolygonShape shape;
	shape.SetAsBox(PixelToMeter(pBlock->origWidth * 0.5f * pBlock->scaleFactor), PixelToMeter(pBlock->origHeight * 0.5f * pBlock->scaleFactor));

	// Body
	b2Body *pBlockBody = World::getWorld()->CreateBody(&BodyDef);

	// Fixture
	b2FixtureDef FixtureDef;
	FixtureDef.shape = &shape;
	FixtureDef.density = 15;
	FixtureDef.friction = 2.5;
	FixtureDef.restitution = 0;
	FixtureDef.userData = pBlock;
	
	pBlockBody->CreateFixture(&FixtureDef);

	// Body points to GameObject
	pBlockBody->SetUserData(pBlock);

	// GameObject points to Body
	pBlock->pBody = pBlockBody;

	return pBlock;

}
void StoneBlock::CreateChunks()
{
	pEmitter->SpawnMultiple(5);
}
void StoneBlock::DeadPhase()
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