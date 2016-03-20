#include "Healty.h"
#include "Piggy.h"
#include "PiggyDead.h"
#include "GameObjectMan.h"

PiggyDead::PiggyDead()
{
}

PiggyDead::~PiggyDead()
{
}
PiggyDead *PiggyDead::GetInstance()
{
	static PiggyDead instance;
	return &instance;
}
void PiggyDead::Enter(Piggy* pPiggy)
{

	TimerMan::CleanObjectEvents(pPiggy);
}

void PiggyDead::Execute(float totalTime, Piggy* pPiggy)
{
	totalTime;
	PigSoundObj::Instance()->Play(SoundType::DEATH);
	pPiggy->DeadPhase();
	//out("---> Death:%x life:%f\n", this->name, this->maxDamage);
	pPiggy->deleteMe = true;
	pPiggy->pBody->SetActive(false);

	// Add to death list
	GameObjectMan::AddToDeleteList(pPiggy);
	



}
void PiggyDead::Exit(Piggy* pPiggy)
{
	pPiggy;
}