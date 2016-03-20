#include <assert.h>

#include "Piggy.h"
#include "PiggyFactory.h"
#include "GraphicsObject_Sprite.h"
#include "PixelToMeter.h"
#include "Box2D.h"
#include "World.h"
#include "GameObjectMan.h"
#include "Level.h"


Piggy * PiggyFactory::Create(GameObjectName::Name gObjName, ImageName::Name imageName, Rect rect)
{

	float scale = Level::getScale(); scale;
	GameObject *pObj = GameObjectMan::Find(GameObjectName::Blocks_Sort);
	// input validation
	assert(pObj);
	GameSortBucket *pSort = (GameSortBucket *)pObj;

	// create the object
	GraphicsObject_Sprite *pSprite = new GraphicsObject_Sprite(imageName, rect);
	Piggy *pPiggy = new Piggy(gObjName, pSprite, pSort);
	pPiggy->angle = 0;
	assert(pPiggy);

	// Do the Box2D setup:
	assert(pPiggy->origWidth == pPiggy->origHeight);

	// Body Def
	b2BodyDef BodyDef;
	BodyDef.type = b2BodyType::b2_dynamicBody;
	BodyDef.position.Set(PixelToMeter(pPiggy->posX), PixelToMeter(pPiggy->posY));
	BodyDef.angle = pPiggy->angle;
	BodyDef.angularDamping = 1.5f;
	BodyDef.linearDamping = 0.0f;

	// Shape
	b2CircleShape Circle;
	// relative - I keep forgetting
	Circle.m_p.x = PixelToMeter(1.20f);
	Circle.m_p.y = PixelToMeter(0.40f);
	Circle.m_radius = PixelToMeter(pPiggy->origWidth * 0.5f);

	// Body
	b2Body *pBirdBody = World::getWorld()->CreateBody(&BodyDef);

	// Fixture
	b2FixtureDef FixtureDef;
	FixtureDef.shape = &Circle;
	FixtureDef.density = 5.0f;
	FixtureDef.friction = 0.3f;
	FixtureDef.restitution = 0.50f;
	FixtureDef.userData = pPiggy;

	pBirdBody->CreateFixture(&FixtureDef);

	// Body points to GameObject
	pBirdBody->SetUserData(pPiggy);

	// GameObject points to Body
	pPiggy->pBody = pBirdBody;

	pPiggy->pBody->SetActive(true);
	return pPiggy;
}