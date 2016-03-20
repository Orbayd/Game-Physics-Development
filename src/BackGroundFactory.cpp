
#include "BackGround.h"
#include "BackGroundFactory.h"
#include "GameObjectMan.h"
#include "PixelToMeter.h"
#include "Ground.h"
#include "World.h"
#include "Sky.h"
BackGround *BackGroundFactory::Create(GameObjectName::Name gObjName, ImageName::Name imageName, Rect rect, const float rot)
{
	GameObject *pObj = GameObjectMan::Find(GameObjectName::BackGround_Sort);
	assert(pObj);
	GameSortBucket *pSortBucket = (GameSortBucket *)pObj;

	GraphicsObject_Sprite *pSprite = new GraphicsObject_Sprite(imageName, rect);
	BackGround *pBackGround = new BackGround(gObjName, pSprite, pSortBucket);
	pBackGround->angle = rot;

	Ground * pGround = new Ground();
	pGround->posX = pBackGround->posX;
	pGround->posY = 45;
	b2BodyDef BodyDef;
	BodyDef.type = b2BodyType::b2_staticBody;
	BodyDef.position.Set(PixelToMeter(pGround->posX), PixelToMeter(pGround->posY));


	// Shape
	b2PolygonShape shape;
	shape.SetAsBox(PixelToMeter(1280), PixelToMeter(10));

	// Body
	b2Body *pBlockBody = World::getWorld()->CreateBody(&BodyDef);

	// Fixture
	b2FixtureDef FixtureDef;
	FixtureDef.shape = &shape;
	FixtureDef.density = 10.0f;
	FixtureDef.friction = 0.3f;
	FixtureDef.restitution = 0.50f;
	FixtureDef.userData = pGround;

	pBlockBody->CreateFixture(&FixtureDef);

	// Body points to GameObject
	pBlockBody->SetUserData(pGround);

	// GameObject points to Body
	pGround->pBody = pBlockBody;
	GameSortBucket * pSort = (GameSortBucket *)GameObjectMan::Find(GameObjectName::StaticObjects_Sort);
	GameObjectMan::Add(pGround, pSort);

	Sky::Create(gObjName, ImageName::Sky, Rect(pBackGround->posX, pBackGround->posY + 1336 * 0.5f +300, 1280, 446*2));
	return pBackGround;
}
