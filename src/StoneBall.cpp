#include "StoneBall.h"
#include "GameObjectMan.h"
#include "PixelToMeter.h"
#include "World.h"
StoneBall::~StoneBall()
{
}

StoneBall::StoneBall(GameObjectName::Name name, GraphicsObject_Sprite *pSprite, GameSortBucket *pSort) :Block(name, pSprite, pSort)
{
	this->maxDamage = 1000.0f;
}
void StoneBall::WorldUpdate(float currentTime)
{

	currentTime;

	// Goal: update the world matrix
	Matrix ScaleF(MatrixScaleType::SCALE, this->scaleFactor, this->scaleFactor, 1.0f);
	Matrix Scale(MatrixScaleType::SCALE, this->scaleX, this->scaleY, 1.0f);
	Matrix Rot(RotType::ROT_Z, this->angle);
	Matrix Trans(MatrixTransType::TRANS, this->posX, this->posY, 0.0f);

	*this->pWorld = ScaleF* Scale * Rot * Trans;

}
StoneBall *StoneBall::Create(GameObjectName::Name gObjName, ImageName::Name imageName, Rect rect, b2BodyType type)
{

	GameObject *pObj = GameObjectMan::Find(GameObjectName::Blocks_Sort);
	// input validation
	assert(pObj);
	GameSortBucket *pSort = (GameSortBucket *)pObj;

	GraphicsObject_Sprite *pSprite = new GraphicsObject_Sprite(imageName, rect);

	StoneBall *pBlock = new StoneBall(gObjName, pSprite, pSort);


	// Body Def
	b2BodyDef BodyDef;
	BodyDef.type = type;
	BodyDef.position.Set(PixelToMeter(pBlock->posX* pBlock->scaleFactor), PixelToMeter(pBlock->posY*pBlock->scaleFactor));
	BodyDef.angle = pBlock->angle;

	// Shape
	b2CircleShape shape;
	// relative - I keep forgetting
	shape.m_p.x = PixelToMeter(0.0f);
	shape.m_p.y = PixelToMeter(0.0f);
	shape.m_radius = PixelToMeter(pBlock->origWidth * 0.5f);

	// Body
	b2Body *pBlockBody = World::getWorld()->CreateBody(&BodyDef);

	// Fixture
	b2FixtureDef FixtureDef;
	FixtureDef.shape = &shape;
	FixtureDef.density = 20.0f;
	FixtureDef.friction = 0.5f;
	FixtureDef.restitution = 0.1f;
	FixtureDef.userData = pBlock;

	pBlockBody->CreateFixture(&FixtureDef);

	// Body points to GameObject
	pBlockBody->SetUserData(pBlock);

	// GameObject points to Body
	pBlock->pBody = pBlockBody;

	return pBlock;
}