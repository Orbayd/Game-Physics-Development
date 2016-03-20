#include "BlueBird.h"
#include "Split.h"
#include "GameObjectMan.h"
#include "PixelToMeter.h"
#include "World.h"

#include "TimerMan.h"
#include "Blink.h"
#include "Simulation.h"
#include "Wait.h"
#include "SoundObject.h"
#include "BlueBirdSound.h"
#include"DefaultState.h"
BlueBird::BlueBird(GameObjectName::Name name, GraphicsObject_Sprite *pSprite, GameSortBucket *pSort) :Bird(name, pSprite, pSort)
{
	this->pAbility = Split::getInstance();
	this->pBirdSdnObj = new BlueBirdSoundObj();
	pbirdState = Wait::GetInstance();
	pbirdState->Enter(this);
	
}

BlueBird::~BlueBird()
{
}
void BlueBird::AddBlinkEvent()
{
	Blink * pBlink = new Blink(this, ImageName::BlueBird, ImageName::BlueBirdBlink);
	TimerMan::AddEvent(Simulation::Instance()->getTotalTime() + 1.0f, pBlink);

}
void BlueBird::PlayWarCry()
{
	this->pGameSprite->SetImage(ImageName::BlueBirdSmile);
	this->pBirdSdnObj->Play(SoundType::BirdWarCry);

}
void BlueBird::ChangeSpriteToFly()
{
	this->pGameSprite->SetImage(ImageName::BlueBirdBlink);
}
void BlueBird::ChangeSpriteToDeath()
{
	this->pGameSprite->SetImage(ImageName::BlueBirdDamaged);
}
BlueBird* BlueBird::Copy(GameObjectName::Name gObjName, GameObject2D  * const copy, b2Vec2 pos)
{
	GraphicsObject_Sprite *  pn = ((GraphicsObject_Sprite*)copy->getGraphicsObject());
	GraphicsObject_Sprite *pSprite = new GraphicsObject_Sprite(pn->pImage->name, Rect(pos.x, pos.y, pn->origWidth, pn->origHeight));
	assert(pSprite);
	GameSortBucket * pSort = (GameSortBucket*)GameObjectMan::Find(GameObjectName::Effects_Sort);
	assert(pSort);
	BlueBird *pBird = new BlueBird(gObjName, pSprite, pSort);
	assert(pBird);
	pBird->CreateBody(pos, 1.0f, copy->angle, copy->pBody->GetLinearVelocity(), 0);
	
	pBird->pbirdState = DefaultState ::GetInstance();
	pBird->pbirdState->Enter(pBird);
	pBird->pBody->SetActive(true);
	pBird->LostAbility();
	return pBird;
}
BlueBird * BlueBird::Create(GameObjectName::Name gObjName, ImageName::Name imageName, Rect rect)
{


	GraphicsObject_Sprite *pSprite = new GraphicsObject_Sprite(imageName, rect);
	assert(pSprite);

	GameSortBucket * pSort = (GameSortBucket*)GameObjectMan::Find(GameObjectName::Birds_Sort);

	BlueBird *pBird = new BlueBird(gObjName, pSprite, pSort);


	pBird->CreateBody(b2Vec2(rect.x, rect.y), 1, 0, b2Vec2(0, 0),0);
	
	assert(pBird);

	return pBird;

}

void BlueBird::CreateBody(b2Vec2 center, float scale, float _angle, b2Vec2 linVel, float angleVel)
{
	center; scale; angle; linVel; angleVel;

	this->angle = _angle;
	this->scaleX = scale;
	this->scaleY = scale;

	b2BodyDef BodyDef;
	BodyDef.type = b2BodyType::b2_dynamicBody;
	BodyDef.angle = this->angle;
	BodyDef.position.Set(PixelToMeter(center.x), PixelToMeter(center.y));
	BodyDef.angle = this->angle;
	BodyDef.active = false;
	BodyDef.angularDamping = 1.5f;
	BodyDef.userData = this;
	BodyDef.linearVelocity.Set((linVel.x), (linVel.y));
	BodyDef.angularVelocity = angleVel;
	// Shape
	b2CircleShape Circle;
	// relative - I keep forgetting
	Circle.m_p.x = PixelToMeter(0.0f);
	Circle.m_p.y = PixelToMeter(0.0f);
	Circle.m_radius = PixelToMeter(this->origWidth * 0.5f);

	// Body
	b2Body *pBirdBody = World::getWorld()->CreateBody(&BodyDef);

	// Fixture
	b2FixtureDef FixtureDef;
	FixtureDef.shape = &Circle;
	FixtureDef.density = 10.0f;
	FixtureDef.friction = 0.3f;
	FixtureDef.restitution = 0.50f;
	FixtureDef.userData = this;

	//Later Add
	FixtureDef.filter.categoryBits = 0x0008;

	pBirdBody->CreateFixture(&FixtureDef);

	

	// GameObject points to Body
	this->pBody = pBirdBody;





}