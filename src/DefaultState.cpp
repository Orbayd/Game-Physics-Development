#include "DefaultState.h"
#include "InputMan.h"
#include "Bird.h"

#include "Dead.h"
#include "TimerMan.h"
#include "SmokeTrailMan.h"
#include "SoundMan.h"
#include "SoundObject.h"
#include "CameraDirector.h"
DefaultState::DefaultState()
{

}

DefaultState::~DefaultState()
{
}
DefaultState *DefaultState::GetInstance()
{
	static DefaultState instance;
	return &instance;
}
void DefaultState::Enter(Bird* pBird)
{

	TimerMan::CleanObjectEvents(pBird);
	pBird->ChangeSpriteToFly();
	


}
void DefaultState::Execute(float totalTime, Bird* pBird)
{
	totalTime;
	pBird;

	//SmokeManager::UpdateP(totalTime, pBird);



}
void DefaultState::Exit(Bird* pBird)
{
	pBird;

}