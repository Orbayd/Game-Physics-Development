#include "Healty.h"
#include "Damaged.h"


PiggyHealty::PiggyHealty()
{
}

PiggyHealty::~PiggyHealty()
{
}
PiggyHealty *PiggyHealty::GetInstance()
{
	static PiggyHealty instance;
	return &instance;
}
void PiggyHealty::Enter(Piggy* pPiggy)
{
	
	OinkEvent *pEvent = new OinkEvent(pPiggy);
	Blink * pBlink = new Blink(pPiggy, ImageName::Piggy_Healty, ImageName::Piggy_HealtyBlink);

	TimerMan::AddEvent(Simulation::Instance()->getTotalTime() + 1.0f, pBlink);
	TimerMan::AddEvent(Simulation::Instance()->getTotalTime() + 4.0f, pEvent);
}

void PiggyHealty::Execute(float totalTime, Piggy* pPiggy)
{
	totalTime;
	pPiggy;
	float it = pPiggy->PendingLifeLeft(); it;
	if (pPiggy->pendingDamage >= pPiggy->maxDamage*0.25f )
	{
		pPiggy->ChangeState(PiggyDamaged::GetInstance());
	}
	
	
}
void PiggyHealty::Exit(Piggy* pPiggy)
{
	TimerMan::CleanObjectEvents(pPiggy, EventName::BLINK);
}