#include "GreenBird.h"
#include "Boomerang.h"
#include "GameObjectMan.h"
#include "PixelToMeter.h"
#include "World.h"



#include "TimerMan.h"
#include "Blink.h"
#include "Simulation.h"
#include "Wait.h"
#include "SoundObject.h"
#include "GreenBirdSound.h"
GreenBird::GreenBird(GameObjectName::Name name, GraphicsObject_Sprite *pSprite, GameSortBucket *pSort) :Bird(name, pSprite, pSort)
{
	this->pAbility = Boomerang::getInstance();
	this->pBirdSdnObj = new GreenBirdSoundObj();
	pbirdState = Wait::GetInstance();
	pbirdState->Enter(this);

}

GreenBird::~GreenBird()
{
}
void GreenBird::AddBlinkEvent()
{
	Blink * pBlink = new Blink(this, ImageName::GreenBird, ImageName::GreenBirdBlink);
	TimerMan::AddEvent(Simulation::Instance()->getTotalTime() + 1.0f, pBlink);

}
void GreenBird::PlayWarCry()
{

	this->pGameSprite->SetImage(ImageName::GreenBirdSmile);
	this->pBirdSdnObj->Play(SoundType::BirdWarCry);

}
void GreenBird::ChangeSpriteToFly()
{
	this->pGameSprite->SetImage(ImageName::GreenBirdBlink);
}
void GreenBird::ChangeSpriteToDeath()
{
	this->pGameSprite->SetImage(ImageName::GreenBirdDamaged);
}
GreenBird * GreenBird::Create(GameObjectName::Name gObjName, ImageName::Name imageName, Rect rect)
{


	GraphicsObject_Sprite *pSprite = new GraphicsObject_Sprite(imageName, rect);
	assert(pSprite);

	GameSortBucket * pSort = (GameSortBucket*)GameObjectMan::Find(GameObjectName::Birds_Sort);

	GreenBird *pBird = new GreenBird(gObjName, pSprite, pSort);


	pBird->CreateBody(b2Vec2(rect.x, rect.y), 1, 0, b2Vec2(0, 0), 0);

	assert(pBird);

	return pBird;

}



void GreenBird::CreateBody(b2Vec2 center, float scale, float angle, b2Vec2 linVel, float angleVel)
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
	Circle.m_p.x = PixelToMeter(-3.0f);
	Circle.m_p.y = PixelToMeter(-5.0f);
	Circle.m_radius = PixelToMeter(this->origWidth * 0.25f);

	// Body
	b2Body *pBirdBody = World::getWorld()->CreateBody(&BodyDef);

	// Fixture
	b2FixtureDef FixtureDef;
	FixtureDef.shape = &Circle;
	FixtureDef.density = 3.5f;
	FixtureDef.friction = 0.3f;
	FixtureDef.restitution = 0.50f;
	FixtureDef.userData = this;

	//Later Add
	FixtureDef.filter.categoryBits = 0x0008;

	pBirdBody->CreateFixture(&FixtureDef);



	// GameObject points to Body
	this->pBody = pBirdBody;

	this->debugColor = Color::Type::Yellow;



}