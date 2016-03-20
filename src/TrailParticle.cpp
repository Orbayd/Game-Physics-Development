#include <assert.h>

#include "TrailParticle.h"
#include "PixelToMeter.h"
#include "World.h"
#include "DebugOut.h"
#include "AzulHelper.h"
#include "Simulation.h"
#include "GameObjectMan.h"


TrailParticle::TrailParticle(GameObjectName::Name name, GraphicsObject_Sprite *pSprite, GameSortBucket *pSort)
	:Particle(name, pSprite, pSort)
{

}

void TrailParticle::WorldUpdate(float currentTime)
{
	AZUL_UNUSED_FLOAT(currentTime);

	// Goal: update the world matrix
	Matrix Scale(MatrixScaleType::SCALE, this->scaleX, this->scaleY, 1.0f);
	Matrix Rot(RotType::ROT_Z, this->angle);
	Matrix Trans(MatrixTransType::TRANS, this->posX, this->posY, 0.0f);

	*this->pWorld = Scale * Rot * Trans;

	//float timeInSec = Simulation::Instance()->getTimeStep();
	//this->lifeTime += timeInSec;


	//this->pendingDamage = this->damage;

	//// test with a small delta
	//if (this->lifeTime >= maxLifeTime)
	//{
	//	// Add to death list
	//	GameObjectMan::AddToDeleteList(this);
	//}
}


TrailParticle *TrailParticle::Create(GameObjectName::Name gObjName, ImageName::Name imageName, Rect rect, GameSortBucket *pSort)
{
	assert(pSort);

	GraphicsObject_Sprite *pSprite = new GraphicsObject_Sprite(imageName, rect);
	assert(pSprite);

	TrailParticle *pParticle = new TrailParticle(gObjName, pSprite, pSort);
	assert(pParticle);

	return pParticle;
}

void TrailParticle::CreateBody(b2Vec2 center, float scale, float _angle, b2Vec2 linVel, float angleVel)
{
	this->angle = _angle;
	this->scaleX = scale;
	this->scaleY = scale;
	this->posX = center.x;
	this->posY = center.y;

	//this->drawSprite = false;
	this->drawDebug = false;

	// Body Def
	b2BodyDef BodyDef;
	BodyDef.type = b2BodyType::b2_dynamicBody;
	BodyDef.angle = _angle;
	BodyDef.fixedRotation = true; // rotation not necessary
	BodyDef.bullet = false; // prevent tunneling at high speed
	BodyDef.linearDamping = 1.0f; // drag due to moving through air
	BodyDef.gravityScale = 0.0f; // ignore gravity
	BodyDef.position.Set(PixelToMeter(center.x), PixelToMeter(center.y)); // start at blast center
	BodyDef.linearVelocity.Set((linVel.x), (linVel.y));
	BodyDef.angularVelocity = angleVel;
	BodyDef.angularDamping = 1.0f;

	// Shape
	b2CircleShape Circle;
	// relative - I keep forgetting
	Circle.m_p.x = PixelToMeter(0.0f);
	Circle.m_p.y = PixelToMeter(0.0f);

	// Might want to make it very small 0.05 ish
	Circle.m_radius = PixelToMeter(this->origWidth * 0.5f);

	// Body
	b2Body *pParticleBody = World::getWorld()->CreateBody(&BodyDef);

	// Fixture
	b2FixtureDef FixtureDef;
	FixtureDef.shape = &Circle;
	FixtureDef.density = 0.0f;
	FixtureDef.friction = 0.0f;
	FixtureDef.restitution = 0.0f;
	FixtureDef.userData = this;
	FixtureDef.isSensor = true;
	FixtureDef.filter.groupIndex = -1; // particles should not collide with each other

	pParticleBody->CreateFixture(&FixtureDef);

	// Body points to GameObject
	pParticleBody->SetUserData(this);

	// GameObject points to Body
	this->pBody = pParticleBody;

}
