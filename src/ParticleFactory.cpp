#include <assert.h>

#include "ParticleFactory.h"
#include "GraphicsObject_Sprite.h"
#include "PixelToMeter.h"
#include "Box2D.h"
#include "World.h"


BombParticle *ParticleFactory::CreateBomb(GameObjectName::Name gObjName, ImageName::Name imageName, Rect rect, GameSortBucket *pSort, b2BodyType type,
	b2Vec2 center, b2Vec2 linVel, float density)
{
	assert(pSort);

	GraphicsObject_Sprite *pSprite = new GraphicsObject_Sprite(imageName, rect);
	BombParticle *pParticle = new BombParticle(gObjName, pSprite, pSort);
	assert(pParticle);
//	pParticle->blastCenter.Set((center.x), (center.y)) ;
	// Do the Box2D setup:
	assert(pParticle->origWidth == pParticle->origHeight);

	// Body Def
	b2BodyDef BodyDef;
	BodyDef.type = type;
	//BodyDef.position.Set(PixelToMeter(pParticle->posX), PixelToMeter(pParticle->posY));
	BodyDef.angle = pParticle->angle;
	BodyDef.fixedRotation = true; // rotation not necessary
	BodyDef.bullet = true; // prevent tunneling at high speed
	BodyDef.linearDamping = 1.0f; // drag due to moving through air
	BodyDef.gravityScale = 1.0f; // ignore gravity
	BodyDef.position.Set(PixelToMeter(center.x),PixelToMeter(center.y)); // start at blast center
	BodyDef.linearVelocity.Set((linVel.x), (linVel.y));

	// Shape
	b2CircleShape Circle;
	// relative - I keep forgetting
	Circle.m_p.x = PixelToMeter(1.20f);
	Circle.m_p.y = PixelToMeter(0.40f);

	// Might want to make it very small 0.05 ish
	Circle.m_radius = PixelToMeter(pParticle->origWidth * 0.5f);

	// Body
	b2Body *pParticleBody = World::getWorld()->CreateBody(&BodyDef);

	// Fixture
	b2FixtureDef FixtureDef;
	FixtureDef.shape = &Circle;
	FixtureDef.density = density;
	FixtureDef.friction = 0.0f;
	FixtureDef.restitution = 0.09f;
	FixtureDef.userData = pParticle;
	FixtureDef.filter.groupIndex = -1; // particles should not collide with each other
	
	//Later Add// Trying Collision Filtering
	FixtureDef.filter.categoryBits = 0x0004;
	FixtureDef.filter.maskBits = 0xFFFF & ~0x0008; //Everthing and not bird;
	//
	pParticleBody->CreateFixture(&FixtureDef);

	// Body points to GameObject
	pParticleBody->SetUserData(pParticle);

	// GameObject points to Body
	pParticle->pBody = pParticleBody;

	return pParticle;
}

Particle *ParticleFactory::CreateChunks(GameObjectName::Name gObjName, ImageName::Name imageName, Rect rect, GameSortBucket *pSort, b2BodyType type,
	b2Vec2 center, b2Vec2 linVel, float density,float _angle)
{

	gObjName; imageName; rect; pSort; type;
	center; linVel; density; _angle;

//	GraphicsObject_Sprite *pSprite = new GraphicsObject_Sprite(imageName, rect);
////	Particle *pParticle = new Particle(gObjName, pSprite, pSort);
////	pParticle->angle = _angle;
//	assert(pParticle);
//
//	// Do the Box2D setup:
//	//assert(pParticle->origWidth == pParticle->origHeight);
//
//	b2BodyDef BodyDef;
//	BodyDef.angle = _angle;
//	
//	BodyDef.type = type;
//	BodyDef.position.Set(PixelToMeter(center.x), PixelToMeter(center.y));
//	BodyDef.angle = pParticle->angle;
//	BodyDef.linearVelocity.Set((linVel.x), (linVel.y));
//	BodyDef.angularVelocity = (-3.0f);
//	
//	BodyDef.linearDamping = 8.0f;
//	BodyDef.fixedRotation = false;
//	BodyDef.gravityScale = 0;
//	BodyDef.angularDamping = 1.0f;
//	BodyDef.active = true;
//	BodyDef.userData = pParticle;
//	// Shape
//	b2CircleShape shape;
//	// relative - I keep forgetting
//	shape.m_p.x = PixelToMeter(0.0f);
//	shape.m_p.y = PixelToMeter(0.0f);
//	shape.m_radius = PixelToMeter(1);
//	
//	// Body
//	b2Body *pParticleBody = World::getWorld()->CreateBody(&BodyDef);
//
//	// Fixture
//	b2FixtureDef FixtureDef;
//	FixtureDef.shape = &shape;
//	FixtureDef.density = density;
//	FixtureDef.friction = 0.3f;
//	FixtureDef.restitution = 0.10f;
//	FixtureDef.userData = pParticle;
//	FixtureDef.filter.categoryBits = 0x0002;
//	FixtureDef.filter.maskBits = (0x0000);
//
//	pParticleBody->CreateFixture(&FixtureDef);
//
//	// GameObject points to Body0,
//	pParticle->pBody = pParticleBody;
//
//
//	
//
//	return pParticle;
	return  0;
}

