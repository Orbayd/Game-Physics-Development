#include "SpeedUp.h"
#include "Bird.h"
#include "GameObjectMan.h"
#include "PixelToMeter.h"
#include "SmokeTrailMan.h"
SpeedUp::SpeedUp()
{
	
}

SpeedUp::~SpeedUp()
{
}

void SpeedUp::Execute(Bird * pbird)
{
	b2Vec2 Vel = pbird->pBody->GetLinearVelocity();
	Vel.Normalize();
	Vel *= 50.0f;
	pbird->pBody->SetLinearVelocity(Vel);
	pbird->getGraphicsObject()->SetImage(ImageName::YellowBirdAbility);
	SmokeManager::AddSmoke(pbird);
}

SpeedUp* SpeedUp::getInstance()
{
	static SpeedUp instance;
	return &instance;


}