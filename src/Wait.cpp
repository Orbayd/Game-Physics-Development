#include "Wait.h"
#include "Bird.h"
#include "GameObjectMan.h"
#include "RubberBand.h"


#include "Ready.h"

Wait::Wait()
{
}

Wait::~Wait()
{
}
Wait *Wait::GetInstance()
{
	static Wait instance;
	return &instance;
}
void Wait::Enter(Bird* pBird)
{
	pBird->AddBlinkEvent();
	pBird->AddJumpEvent();
}

void Wait::Execute(float totalTime, Bird* pBird)
{
	totalTime;
	pBird;

//	Bird *pBird =(Bird*) GameObjectMan::getBird();
		//out("---> Death:%x life:%f\n", this->name, this->life);
	Bird * activeBird = (Bird*)GameObjectMan::getActiveBird();
	if (activeBird == pBird )
	{
		pBird->ChangeState(Ready::GetInstance());
	
	}

}
void Wait::Exit(Bird* pBird)
{
	pBird;
}