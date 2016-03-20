#ifndef WARCRY_H
#define WARCRY_H

#include <assert.h>
#include "TimerEvent.h"
#include "TimerMan.h"
#include "Piggy.h"
#include "PigSounds.h"
class OinkEvent : public TimerEvent
{
public:
	OinkEvent(GameObject2D *pObj)
	{
		this->pGobj = pObj;
		this->eName = EventName::OINK;
	}

	virtual void Execute(float currTime) override
	{
		if (pGobj == 0)
		{
			TimerMan::RemoveEvent(this);
			return;
		}
		
		
		PigSoundObj::Instance()->Play(SoundType::OINK);


		float nextEventTime = 8 * (rand() % 10) / 10.0f + 1.0f;
		TimerMan::AddEvent(currTime + nextEventTime, new OinkEvent(pGobj));
		TimerMan::RemoveEvent(this);
	}


};



#endif