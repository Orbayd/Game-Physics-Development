#include <assert.h>

#include "WoodPlatfomFactory.h"
#include "BlockFactory.h"
#include "GraphicsObject_Sprite.h"
#include "PixelToMeter.h"
#include "Box2D.h"
#include "World.h"
#include "GameObjectMan.h"
#include "Level.h"



WoodPlatform *PlatformFactory::Create(GameObjectName::Name gObjName, ImageName::Name imageName, Rect rect, const float rot, b2BodyType type)
{
	
	GameObject *pObj = GameObjectMan::Find(GameObjectName::Blocks_Sort);
	// input validation
	assert(pObj);
	GameSortBucket *pSort = (GameSortBucket *)pObj;

	GraphicsObject_Sprite *pSprite = new GraphicsObject_Sprite(imageName, rect);
	WoodPlatform *pWoodPlatform = new WoodPlatform(gObjName, pSprite, pSort);
	pWoodPlatform->scaleFactor = Level::getScale();
	pWoodPlatform->angle = rot;

	assert(pWoodPlatform);

	// Body Def
	b2BodyDef BodyDef;
	BodyDef.type = type;
	BodyDef.position.Set(PixelToMeter(pWoodPlatform->posX* pWoodPlatform->scaleFactor), PixelToMeter(pWoodPlatform->posY*pWoodPlatform->scaleFactor));
	BodyDef.angle = pWoodPlatform->angle;

	// Shape
	b2PolygonShape shape;
	shape.SetAsBox(PixelToMeter(pWoodPlatform->origWidth * 0.5f * pWoodPlatform->scaleFactor), PixelToMeter(pWoodPlatform->origHeight * 0.5f * pWoodPlatform->scaleFactor));

	// Body
	b2Body *pBlockBody = World::getWorld()->CreateBody(&BodyDef);

	// Fixture
	b2FixtureDef FixtureDef;
	FixtureDef.shape = &shape;
	FixtureDef.density = 10.0f;
	FixtureDef.friction = 0.3f;
	FixtureDef.restitution = 0.50f;
	FixtureDef.userData = pWoodPlatform;

	pBlockBody->CreateFixture(&FixtureDef);

	// Body points to GameObject
	pBlockBody->SetUserData(pWoodPlatform);

	// GameObject points to Body
	pWoodPlatform->pBody = pBlockBody;

	return pWoodPlatform;
}
