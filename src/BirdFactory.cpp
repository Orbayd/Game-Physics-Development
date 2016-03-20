#include <assert.h>

#include "Bird.h"
#include "BirdFactory.h"
#include "GraphicsObject_Sprite.h"
#include "PixelToMeter.h"
#include "Box2D.h"
#include "World.h"
#include "GameObjectMan.h"
#include "Level.h"
Bird *BirdFactory::Create(GameObjectName::Name gObjName, ImageName::Name imageName, Rect rect)
{
	gObjName; imageName; rect;
//	float scale = Level::getScale(); scale;
//	GameObject *pObj = GameObjectMan::Find(GameObjectName::Birds_Sort);
//	// input validation
//	assert(pObj);
//	GameSortBucket *pSort = (GameSortBucket *)pObj;
//
//	// create the object
//	GraphicsObject_Sprite *pSprite = new GraphicsObject_Sprite(imageName, rect);
////	Bird *pBird = new Bird(gObjName, pSprite, pSort);
//	pBird->angle = 0;
//	assert(pBird);
//
//	// Do the Box2D setup:
//	assert(pBird->origWidth == pBird->origHeight);
//
//	// Body Def
//	b2BodyDef BodyDef;
//	BodyDef.type = b2BodyType::b2_dynamicBody;
//	BodyDef.position.Set(PixelToMeter(pBird->posX), PixelToMeter(pBird->posY));
//	BodyDef.angle = pBird->angle;
//	
//	// Shape
//	b2CircleShape Circle;
//	// relative - I keep forgetting
//	Circle.m_p.x = PixelToMeter(1.20f);
//	Circle.m_p.y = PixelToMeter(0.40f);
//	Circle.m_radius = PixelToMeter(pBird->origWidth * 0.5f);
//
//	// Body
//	b2Body *pBirdBody = World::getWorld()->CreateBody(&BodyDef);
//
//	// Fixture
//	b2FixtureDef FixtureDef;
//	FixtureDef.shape = &Circle;
//	FixtureDef.density = 10.0f;
//	FixtureDef.friction = 0.3f;
//	FixtureDef.restitution = 0.50f;
//	FixtureDef.userData = pBird;
//	
//	//Later Add
//	FixtureDef.filter.categoryBits = 0x0008;
//
//	pBirdBody->CreateFixture(&FixtureDef);
//
//	// Body points to GameObject
//	pBirdBody->SetUserData(pBird);
//
//	// GameObject points to Body
//	pBird->pBody = pBirdBody;
//
//	//pBird->pBody->SetGravityScale(0.0f);
//	//pBird->pBody->SetAwake(false);
//	pBird->pBody->SetActive(false);
//	pBird->pBody->SetAngularDamping(1.5f);
//	return pBird;
	return 0;
}




