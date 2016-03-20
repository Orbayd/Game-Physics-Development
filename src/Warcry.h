#ifndef WARCRY_H
#define WARCRY_H

#include <assert.h>
#include "TimerEvent.h"
#include "Bird.h"
#include "TimerMan.h"
#include "Bird.h"
class WarCry : public TimerEvent
{
public:
	WarCry(GameObject2D *pObj)
	{
		this->pGobj = pObj;
		this->eName = EventName::BLINK;
	}

	virtual void Execute(float currTime) override
	{
		if (pGobj == 0)
		{
			TimerMan::RemoveEvent(this);
			return;
		}
		Bird * pBird = (Bird*)pGobj;
		pBird->PlayWarCry();

		std::srand((unsigned int)Simulation::Instance()->getTotalTime()); // use current time as seed for random generator
		float nextEventTime = 8 * (std::rand() % 10) / 10.0f + std::rand() % 8;
		TimerMan::AddEvent(currTime + nextEventTime, new WarCry(pGobj));
		TimerMan::RemoveEvent(this);
	}


};



#endif