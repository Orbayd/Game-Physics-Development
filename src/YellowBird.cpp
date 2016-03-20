#include "YellowBird.h"
#include "SpeedUp.h"
#include "GameObjectMan.h"
#include "PixelToMeter.h"
#include "World.h"

#include "Blink.h"
#include "TimerMan.h"
#include "Simulation.h"
#include "Wait.h"
#include "SoundObject.h"
#include "YellowBirdSound.h"
YellowBird::YellowBird(GameObjectName::Name name, GraphicsObject_Sprite *pSprite, GameSortBucket *pSort) :Bird(name, pSprite, pSort)
{
	this->pAbility = SpeedUp::getInstance();
	pbirdState = Wait::GetInstance();
	pbirdState->Enter(this);
	
	this->pBirdSdnObj = new YellowBirdSoundObj();
}

YellowBird::~YellowBird()
{
}
void YellowBird::PlayWarCry()
{

	this->pGameSprite->SetImage(ImageName::YellowBirdSmile);
	this->pBirdSdnObj->Play(SoundType::BirdWarCry);
}

void YellowBird::AddBlinkEvent()
{
	Blink * pBlink = new Blink(this, ImageName::YellowBird, ImageName::YellowBirdBlink);
	TimerMan::AddEvent(Simulation::Instance()->getTotalTime() + 1.0f, pBlink);

}
void YellowBird::ChangeSpriteToFly()
{
	this->pGameSprite->SetImage(ImageName::YellowBirdFly);
}
void YellowBird::ChangeSpriteToDeath()
{
	this->pGameSprite->SetImage(ImageName::YellowBirdDamaged);
}
YellowBird * YellowBird::Create(GameObjectName::Name gObjName, ImageName::Name imageName, Rect rect)
{


	GraphicsObject_Sprite *pSprite = new GraphicsObject_Sprite(imageName, rect);
	assert(pSprite);

	GameSortBucket * pSort = (GameSortBucket*)GameObjectMan::Find(GameObjectName::Birds_Sort);

	YellowBird *pBird = new YellowBird(gObjName, pSprite, pSort);


	pBird->CreateBody(b2Vec2(rect.x, rect.y), 1, 0, b2Vec2(0, 0), 0);

	assert(pBird);

	return pBird;

}

void YellowBird::CreateBody(b2Vec2 center, float scale, float angle, b2Vec2 linVel, float angleVel)
{
	center; scale; angle; linVel; angleVel;

	b2BodyDef BodyDef;
	BodyDef.type = b2BodyType::b2_dynamicBody;
	BodyDef.position.Set(PixelToMeter(this->posX), PixelToMeter(this->posY));
	BodyDef.angle = this->angle;
	BodyDef.active = false;
	BodyDef.angularDamping = 1.5f;
	BodyDef.userData = this;
	BodyDef.bullet = true;
	// Shape
	b2CircleShape Circle;
	// relative - I keep forgetting
	Circle.m_p.x = PixelToMeter(0.0f);
	Circle.m_p.y = PixelToMeter(-5.0f);
	Circle.m_radius = PixelToMeter(this->origWidth * 0.5f);

	// Body
	b2Body *pBirdBody = World::getWorld()->CreateBody(&BodyDef);

	// Fixture
	b2FixtureDef FixtureDef;
	FixtureDef.shape = &Circle;
	FixtureDef.density = 3.0f;
	FixtureDef.friction = 0.3f;
	FixtureDef.restitution = 0.50f;
	FixtureDef.userData = this;

	//Later Add
	FixtureDef.filter.categoryBits = 0x0008;

	pBirdBody->CreateFixture(&FixtureDef);



	// GameObject points to Body
	this->pBody = pBirdBody;





}