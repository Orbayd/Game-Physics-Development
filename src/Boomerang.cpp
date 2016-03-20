#include "Boomerang.h"
#include "Bird.h"
#include "GameObjectMan.h"
#include "PixelToMeter.h"

#include "BoomerangEvent.h"
#include "TimerMan.h"
#include "Simulation.h"
Boomerang::Boomerang()
{

}

Boomerang::~Boomerang()
{
}

void Boomerang::Execute(Bird * pbird)
{
	pbird->pBody->SetAngularVelocity(50.0f);
	BoomerangEvent *pEvent = new BoomerangEvent(pbird, -2 * pbird->pBody->GetLinearVelocity().x);
	pbird->getGraphicsObject()->SetImage(ImageName::GreenBirdAbility);
	TimerMan::AddEvent(Simulation::Instance()->getTotalTime() + 0.0f, pEvent);
}

Boomerang* Boomerang::getInstance()
{
	static Boomerang instance;
	return &instance;


}