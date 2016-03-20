#include "Healty.h"
#include "Piggy.h"
#include "HeavyDamaged.h"
#include "PiggyDead.h"
PiggyHeavyDmged::PiggyHeavyDmged()
{
}

PiggyHeavyDmged::~PiggyHeavyDmged()
{
}
PiggyHeavyDmged *PiggyHeavyDmged::GetInstance()
{
	static PiggyHeavyDmged instance;
	return &instance;
}
void PiggyHeavyDmged::Enter(Piggy* pPiggy)
{
	Blink * pBlink = new Blink(pPiggy, ImageName::Piggy_HeavyDmged, ImageName::Piggy_HeavyDmgedBlink);
	TimerMan::AddEvent(Simulation::Instance()->getTotalTime() + 1.0f, pBlink);
}

void PiggyHeavyDmged::Execute(float totalTime, Piggy* pPiggy)
{
	totalTime;
	pPiggy;

	if (pPiggy->pendingDamage >= pPiggy->maxDamage)
	{
		pPiggy->ChangeState(PiggyDead::GetInstance());
	}

}
void PiggyHeavyDmged::Exit(Piggy* pPiggy)
{
	TimerMan::CleanObjectEvents(pPiggy, EventName::BLINK);
}