#include "Helmet.h"
#include "GameObjectMan.h"
#include "PixelToMeter.h"
#include "World.h"

Helmet::~Helmet()
{
}
Helmet::Helmet(GameObjectName::Name name, GraphicsObject_Sprite *pSprite, GameSortBucket *pSort)
	:GameObject2D(name, pSprite)
{
	GameObjectMan::Add(this, pSort);

	this->maxDamage = 20.0;

	
}
Helmet * Helmet::Create(GameObjectName::Name gObjName, ImageName::Name imageName, Rect rect)
{

	GameObject *pObj = GameObjectMan::Find(GameObjectName::Blocks_Sort);
	// input validation
	assert(pObj);
	GameSortBucket *pSort = (GameSortBucket *)pObj;

	// create the object
	GraphicsObject_Sprite *pSprite = new GraphicsObject_Sprite(imageName, rect);
	Helmet *pHelmet = new Helmet(gObjName, pSprite, pSort);
	pHelmet->angle = 0;

	b2BodyDef BodyDef;
	BodyDef.type = b2BodyType::b2_dynamicBody;
	BodyDef.position.Set(PixelToMeter(pHelmet->posX), PixelToMeter(pHelmet->posY));
	BodyDef.angle = pHelmet->angle;

	// Shape
	b2PolygonShape shape;
	shape.SetAsBox(PixelToMeter(pHelmet->origWidth * 0.25f), PixelToMeter(pHelmet->origHeight * 0.25f ));

	// Body
	b2Body *pBlockBody = World::getWorld()->CreateBody(&BodyDef);

	// Fixture
	b2FixtureDef FixtureDef;
	FixtureDef.shape = &shape;
	FixtureDef.density = 0.1f;
	FixtureDef.friction = 1.0f;
	FixtureDef.restitution = 0.2f;
	FixtureDef.userData = pHelmet;

	pBlockBody->CreateFixture(&FixtureDef);

	// Body points to GameObject
	pBlockBody->SetUserData(pHelmet);

	// GameObject points to Body
	pHelmet->pBody = pBlockBody;

	return pHelmet;
}
void Helmet::WorldUpdate(float currentTime)
{
	(currentTime);

	// Goal: update the world matrix
	
	Matrix Scale(MatrixScaleType::SCALE, this->scaleX, this->scaleY, 1.0f);
	Matrix Rot(RotType::ROT_Z, this->angle);
	Matrix Trans(MatrixTransType::TRANS, this->posX, this->posY, 0.0f);

	*this->pWorld =  Scale * Rot * Trans;

	

}