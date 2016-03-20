#include <assert.h>

#include "Block.h"
#include "BlockFactory.h"
#include "GraphicsObject_Sprite.h"
#include "PixelToMeter.h"
#include "Box2D.h"
#include "World.h"
#include "GameObjectMan.h"
#include "Level.h"
#include "WoodBlock.h"
#include "StoneBlock.h"
#include "GlassBlock.h"


Block *BlockFactory::Create(GameObjectName::Name gObjName, ImageName::Name imageName, Rect rect, const float rot, b2BodyType type)
{
	GameObject *pObj = GameObjectMan::Find(GameObjectName::Blocks_Sort);
	// input validation
	assert(pObj);
	GameSortBucket *pSort = (GameSortBucket *)pObj;

	GraphicsObject_Sprite *pSprite = new GraphicsObject_Sprite( imageName, rect );

	Block *pBlock = 0;
	if (imageName == ImageName::LongWoodBlock_Healty){
		
		pBlock = new WoodBlock(gObjName, pSprite, pSort);
		pBlock->angle = rot;
		pBlock->scaleFactor = Level::getScale();
		assert(pBlock);
		CreateBody(pBlock, type, 6.0f, 0.5f, 0.1f);
	}
	else if (imageName == ImageName::GlassBlock_Healty){

		pBlock = new GlassBlock(gObjName, pSprite, pSort);
		pBlock->angle = rot;
		pBlock->scaleFactor = Level::getScale();
		assert(pBlock);
		CreateBody(pBlock, type, 6.0f, 0.5f, 0.1f);
	}
	else if (imageName == ImageName::StoneBlock_Healty){

		pBlock = new StoneBlock(gObjName, pSprite, pSort);
		pBlock->angle = rot;
		pBlock->scaleFactor = Level::getScale();
		assert(pBlock);
		CreateBody(pBlock, type, 20.0f, 0.5f, 0.1f);
	}
	else
		assert(pBlock);

	return pBlock;
}
void BlockFactory::CreateBody(Block * pBlock , b2BodyType type, const  float density, const  float friction, const  float restution)
{

	// Body Def
	b2BodyDef BodyDef;
	BodyDef.type = type;
	BodyDef.position.Set(PixelToMeter(pBlock->posX* pBlock->scaleFactor), PixelToMeter(pBlock->posY*pBlock->scaleFactor));
	BodyDef.angle = pBlock->angle;

	// Shape
	b2PolygonShape shape;
	shape.SetAsBox(PixelToMeter(pBlock->origWidth * 0.5f * pBlock->scaleFactor), PixelToMeter(pBlock->origHeight * 0.5f * pBlock->scaleFactor));

	// Body
	b2Body *pBlockBody = World::getWorld()->CreateBody(&BodyDef);

	// Fixture
	b2FixtureDef FixtureDef;
	FixtureDef.shape = &shape;
	FixtureDef.density = density;
	FixtureDef.friction = friction;
	FixtureDef.restitution = restution;
	FixtureDef.userData = pBlock;

	pBlockBody->CreateFixture(&FixtureDef);

	// Body points to GameObject
	pBlockBody->SetUserData(pBlock);

	// GameObject points to Body
	pBlock->pBody = pBlockBody;

}