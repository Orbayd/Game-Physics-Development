#include "RedBird.h"
#include "BirdAbility.h"
#include "GameObjectMan.h"
#include "PixelToMeter.h"
#include "World.h"

#include "Wait.h"
#include "RedBirdSound.h"
#include "TimerMan.h"
#include "Blink.h"
#include "Jump.h"
#include "Warcry.h"
#include "SoundObject.h"
RedBird::RedBird(GameObjectName::Name name, GraphicsObject_Sprite *pSprite, GameSortBucket *pSort) :Bird(name, pSprite, pSort)
{
	this->pAbility = (Ability*)NoAbility::getInstance();
	this->pBirdSdnObj = new RedBirdSoundObj();
	pbirdState = Wait::GetInstance();
	pbirdState->Enter(this);
	
}

RedBird::~RedBird()
{
}

void RedBird::AddBlinkEvent()
{
	Blink * pBlink = new Blink(this, ImageName::RedBird, ImageName::RedBirdBlink);
	TimerMan::AddEvent(Simulation::Instance()->getTotalTime() + 1.0f, pBlink);

	
}
void RedBird::PlayWarCry()
{
	this->pGameSprite->SetImage(ImageName::RedBirdSmile);
	//SoundManager::Play("../../data/bird misc a6.wav");

}
void RedBird::ChangeSpriteToFly()
{
	this->pGameSprite->SetImage(ImageName::RedBirdBlink);
}
void RedBird::ChangeSpriteToDeath()
{
	this->pGameSprite->SetImage(ImageName::RedBirdDamaged);
}
RedBird * RedBird::Create(GameObjectName::Name gObjName, ImageName::Name imageName, Rect rect)
{


	GraphicsObject_Sprite *pSprite = new GraphicsObject_Sprite(imageName, rect);
	assert(pSprite);

	GameSortBucket * pSort = (GameSortBucket*)GameObjectMan::Find(GameObjectName::Birds_Sort);

	RedBird *pBird = new RedBird(gObjName, pSprite, pSort);


	pBird->CreateBody(b2Vec2(rect.x, rect.y), 1, 0, b2Vec2(0, 0), 0);

	assert(pBird);

	return pBird;

}

void RedBird::CreateBody(b2Vec2 center, float scale, float angle, b2Vec2 linVel, float angleVel)
{
	center; scale; angle; linVel; angleVel;

	b2BodyDef BodyDef;
	BodyDef.type = b2BodyType::b2_dynamicBody;
	BodyDef.position.Set(PixelToMeter(this->posX), PixelToMeter(this->posY));
	BodyDef.angle = this->angle;
	BodyDef.active = false;
	BodyDef.angularDamping = 1.5f;
	BodyDef.userData = this;
	// Shape
	b2CircleShape Circle;
	// relative - I keep forgetting
	Circle.m_p.x = PixelToMeter(1.20f);
	Circle.m_p.y = PixelToMeter(0.40f);
	Circle.m_radius = PixelToMeter(this->origWidth * 0.5f);

	// Body
	b2Body *pBirdBody = World::getWorld()->CreateBody(&BodyDef);

	// Fixture
	b2FixtureDef FixtureDef;
	FixtureDef.shape = &Circle;
	FixtureDef.density = 5.0f;
	FixtureDef.friction = 0.3f;
	FixtureDef.restitution = 0.50f;
	FixtureDef.userData = this;

	//Later Add
	FixtureDef.filter.categoryBits = 0x0008;

	pBirdBody->CreateFixture(&FixtureDef);



	// GameObject points to Body
	this->pBody = pBirdBody;

	this->debugColor = Color::Type::Red;



}