#include "Healty.h"
#include "Damaged.h"
#include "HeavyDamaged.h"
PiggyDamaged::PiggyDamaged()
{
}

PiggyDamaged::~PiggyDamaged()
{
}
PiggyDamaged *PiggyDamaged::GetInstance()
{
	static PiggyDamaged instance;
	return &instance;
}
void PiggyDamaged::Enter(Piggy* pPiggy)
{
	Blink * pBlink = new Blink(pPiggy, ImageName::Piggy_Dmged, ImageName::Piggy_DmgedBlink);
	TimerMan::AddEvent(Simulation::Instance()->getTotalTime() + 1.0f, pBlink);
	
}

void PiggyDamaged::Execute(float totalTime, Piggy* pPiggy)
{
	totalTime;
	pPiggy;
	if (pPiggy->pendingDamage >= pPiggy->maxDamage*0.50f)
	{
		pPiggy->ChangeState(PiggyHeavyDmged::GetInstance());
	}


}
void PiggyDamaged::Exit(Piggy* pPiggy)
{
	TimerMan::CleanObjectEvents(pPiggy, EventName::BLINK);
}