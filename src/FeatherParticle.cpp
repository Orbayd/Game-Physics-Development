#include <assert.h>

#include "FeatherParticle.h"
#include "PixelToMeter.h"
#include "World.h"

#include "GameObjectMan.h"
#include "AzulHelper.h"
#include "Simulation.h"
FeatherParticle::FeatherParticle(GameObjectName::Name name, GraphicsObject_Sprite *pSprite, GameSortBucket *pSort)
	:Particle(name,pSprite,pSort)
{

}

FeatherParticle *FeatherParticle::Create(GameObjectName::Name gObjName, ImageName::Name imageName, Rect rect, GameSortBucket *pSort)
{
	assert(pSort);

	GraphicsObject_Sprite *pSprite = new GraphicsObject_Sprite(imageName, rect);
	assert(pSprite);

	FeatherParticle *pParticle = new FeatherParticle(gObjName, pSprite, pSort);
	assert(pParticle);

	return pParticle;
}

void FeatherParticle::CreateBody(b2Vec2 center, float scale, float _angle, b2Vec2 linVel, float angleVel)
{
	this->angle = _angle;
	this->scaleX = scale;
	this->scaleY = scale;
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
	Circle.m_radius = PixelToMeter(10.0f * 0.5f);

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

void FeatherParticle::WorldUpdate(float currentTime)
{
	currentTime;
	AZUL_UNUSED_FLOAT(currentTime);

	// Goal: update the world matrix
	Matrix Scale(MatrixScaleType::SCALE, this->scaleX, this->scaleY, 1.0f);
	Matrix Rot(RotType::ROT_Z, this->angle);
	Matrix Trans(MatrixTransType::TRANS, this->posX, this->posY, 0.0f);

	*this->pWorld = Scale * Rot * Trans;

	float timeInSec = Simulation::Instance()->getTimeStep();
	this->lifeTime += timeInSec;

	// add schrink
	if (timeInSec > 0.0f)
	{
		this->scaleX *= 0.99f;
		this->scaleY *= 0.99f;
	}

	//	this->pendingDamage = this->damage;

	// test with a small delta
	if (this->lifeTime >= maxLifeTime)
	{
		this->deleteMe = true;
		// Add to death list
		GameObjectMan::AddToDeleteList(this);
	}

}
