#include <assert.h>

#include "Egg.h"
#include "PixelToMeter.h"
#include "World.h"

#include "GameObjectMan.h"
#include "Simulation.h"
#include "AzulHelper.h"
Egg::Egg(GameObjectName::Name name, GraphicsObject_Sprite *pSprite, GameSortBucket *pSort)
	:Particle(name, pSprite, pSort)
{
	this->maxDamage = 20.0f;
}

Egg *Egg::Create(GameObjectName::Name gObjName, ImageName::Name imageName, Rect rect, GameSortBucket *pSort)
{
	assert(pSort);

	GraphicsObject_Sprite *pSprite = new GraphicsObject_Sprite(imageName, rect);
	assert(pSprite);

	Egg *pParticle = new Egg(gObjName, pSprite, pSort);
	assert(pParticle);

	return pParticle;
}

void Egg::CreateBody(b2Vec2 center, float scale, float _angle, b2Vec2 linVel, float angleVel)
{
	this->angle = _angle;
	this->scaleX = scale;
	this->scaleY = scale;
	
	//this->drawSprite = false;
	//this->drawDebug = false;

	// Body Def
	b2BodyDef BodyDef;
	BodyDef.type = b2BodyType::b2_dynamicBody;
	BodyDef.angle = this->angle;
	BodyDef.fixedRotation = true; // rotation not necessary
	BodyDef.bullet = true; // prevent tunneling at high speed
	//BodyDef.linearDamping = 1.0f; // drag due to moving through air
	BodyDef.gravityScale = 1.0f; // ignore gravity
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
	FixtureDef.density = 6.0f;
	FixtureDef.friction = 0.0f;
	FixtureDef.restitution = 0.7f;
	FixtureDef.userData = this;
	FixtureDef.isSensor = false;
	FixtureDef.filter.groupIndex = -1; // particles should not collide with each other
	//Later Add// Trying Collision Filtering
	FixtureDef.filter.categoryBits = 0x0004;
	FixtureDef.filter.maskBits = 0xFFFF & ~0x0008; //Everthing and not bird;

	pParticleBody->CreateFixture(&FixtureDef);

	// Body points to GameObject
	pParticleBody->SetUserData(this);

	// GameObject points to Body
	this->pBody = pParticleBody;

}
void Egg::WorldUpdate(float currentTime)
{
	AZUL_UNUSED_FLOAT(currentTime);

	// Goal: update the world matrix
	Matrix Scale(MatrixScaleType::SCALE, this->scaleX, this->scaleY, 1.0f);
	Matrix Rot(RotType::ROT_Z, this->angle);
	Matrix Trans(MatrixTransType::TRANS, this->posX, this->posY, 0.0f);

	*this->pWorld = Scale * Rot * Trans;

	float timeInSec = Simulation::Instance()->getTimeStep();
	this->lifeTime += timeInSec;

	

	if(this->damage >= (this->maxDamage - 0.01f))
	{
		this->deleteMe = true;
		//	// Add to death list
			GameObjectMan::AddToDeleteList(this);
	}




}
