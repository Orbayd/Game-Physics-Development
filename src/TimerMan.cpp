#include <assert.h>
#include "TimerMan.h"
#include "Simulation.h"

void TimerMan::Create()
{
	TimerMan *pTimeMan = TimerMan::privInstance();
	assert(pTimeMan);

	pTimeMan->pActive = 0;
	pTimeMan->currTime = 0.0f;
}

TimerMan *TimerMan::privInstance()
{
	static TimerMan timerMan;
	return &timerMan;
}

void TimerMan::AddEvent(float TimeInSec, TimerEvent *pEvent)
{
	TimerMan *pTimeMan = TimerMan::privInstance();
	assert(pTimeMan);

	pEvent->TriggerTime = TimeInSec;

	pTimeMan->privAddToFront(pEvent);
}

void TimerMan::RemoveEvent(TimerEvent *pEvent)
{
	TimerMan *pTimeMan = TimerMan::privInstance();
	assert(pTimeMan);

	pTimeMan->privRemoveFromList(pEvent);
}

void TimerMan::privRemoveFromList(TimerEvent *pEvent)
{
	if (pEvent->prev == 0 && pEvent->next == 0)
	{   // only on list
		this->pActive = 0;
	}
	else if (pEvent->prev == 0 && pEvent->next != 0)
	{   // first on list
		this->pActive = (TimerEvent *)pEvent->next;
		this->pActive->prev = 0;
	}
	else if (pEvent->prev != 0 && pEvent->next == 0)
	{    // last on list
		pEvent->prev->next = 0;
	}
	else
	{	// middle of list
		pEvent->prev->next = pEvent->next;
		pEvent->next->prev = pEvent->prev;
	}

	delete pEvent;
}

void TimerMan::privAddToFront(TimerEvent *pEvent)
{
	if (pActive == 0)
	{
		pActive = pEvent;
		pEvent->next = 0;
		pEvent->prev = 0;
	}
	else
	{
		pEvent->next = pActive;
		pEvent->prev = 0;
		pActive->prev = pEvent;
		pActive = pEvent;
	}
}


void TimerMan::Update()
{
	TimerMan *pTimeMan = TimerMan::privInstance();
	assert(pTimeMan);

	pTimeMan->currTime = Simulation::Instance()->getTotalTime();
	// WALK the list
	TimerEvent *pEvent = pTimeMan->pActive;

	while (pEvent != 0)
	{
		TimerEvent *pEvent_next = (TimerEvent *)pEvent->next;
		if (pTimeMan->currTime >= pEvent->TriggerTime)
		{
			pEvent->Execute(pTimeMan->currTime);
		}

		pEvent = pEvent_next;// (TimerEvent *)pEvent->next;
	}

}

void TimerMan::CleanObjectEvents(GameObject2D *pGobj)
{
	TimerMan *pTimeMan = TimerMan::privInstance();
	assert(pTimeMan);
	// WALK the list
	TimerEvent *pEvent = pTimeMan->pActive;

	while (pEvent != 0)
	{
		TimerEvent *pEvent_next = (TimerEvent *)pEvent->next;
		if (pEvent->pGobj == pGobj)
		{
			pTimeMan->RemoveEvent(pEvent);
		}

		pEvent = pEvent_next;
	}
}
void TimerMan::CleanObjectEvents(GameObject2D *pGobj,EventName::Name eName)
{
	TimerMan *pTimeMan = TimerMan::privInstance();
	assert(pTimeMan);
	// WALK the list
	TimerEvent *pEvent = pTimeMan->pActive;

	while (pEvent != 0)
	{
		TimerEvent *pEvent_next = (TimerEvent *)pEvent->next;
		if (pEvent->pGobj == pGobj && pEvent->eName ==eName)
		{
			pTimeMan->RemoveEvent(pEvent);
		}

		pEvent = pEvent_next;
	}
}