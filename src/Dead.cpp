#include "Dead.h"
#include "Ready.h"
#include "GameObjectMan.h"

#include "Bird.h"
#include "TimerMan.h"
#include "SoundMan.h"

Dead::Dead()
{
}

Dead::~Dead()
{
}
Dead *Dead::GetInstance()
{
	static Dead instance;
	return &instance;
}
void Dead::Enter(Bird* pBird)
{
	pBird->ChangeSpriteToDeath();
	
	Bird * pSibling = (Bird*)pBird->getSibling();
	if (pSibling != 0)
	{
		GameObjectMan::setActiveBird(pSibling);
		pSibling->ChangeState(Ready::GetInstance());
	}
	
}
void Dead::Execute(float totalTime, Bird* pBird)
{
	totalTime;
	pBird;

	float linVel = pBird->pBody->GetLinearVelocity().Length();
	float angVel = pBird->pBody->GetAngularVelocity();
	if (linVel <1.0f && angVel < 1.0f)
	{
		pBird->DeadPhase();
	}

}
void Dead::Exit(Bird* pBird)
{
	pBird;
}