#include "Flying.h"
#include "InputMan.h"
#include "Bird.h"

#include "Dead.h"
#include "TimerMan.h"
#include "SmokeTrailMan.h"
#include "SoundMan.h"
#include "SoundObject.h"
#include "CameraDirector.h"
Fly::Fly()
{
	
}

Fly::~Fly()
{
}
Fly *Fly::GetInstance()
{
	static Fly instance;
	return &instance;
}
void Fly::Enter(Bird* pBird)
{
	
	TimerMan::CleanObjectEvents(pBird);
	pBird->ChangeSpriteToFly();
	pBird->pBirdSdnObj->Play(SoundType::BIRDFLY);

	
}
void Fly::Execute(float totalTime, Bird* pBird)
{
	totalTime;
	pBird;
	Keyboard *key = InputMan::GetKeyboard();
	
	SmokeManager::Update(totalTime, pBird);
	CameraDirector::Update(pBird);
	if (key->GetKeyState(AZUL_KEY::KEY_X))
	{
		pBird->ExecuteAbility();
		
		pBird->LostAbility();
	}



}
void Fly::Exit(Bird* pBird)
{
	pBird;
	SmokeManager::SwitchBuckets();
	
}