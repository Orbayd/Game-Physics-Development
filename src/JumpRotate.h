#ifndef JUMP_ROTATE_H
#define JUMP_ROTATE_H

#include <assert.h>
#include "TimerEvent.h"
#include "Bird.h"
#include "TimerMan.h"

class JumpRotate : public TimerEvent
{
public:
	JumpRotate(GameObject2D *pObj)
	{
		this->pGobj = pObj;
		this->eName = EventName::JUMP;
	}

	virtual void Execute(float currTime) override
	{
		if (pGobj == 0)
		{
			TimerMan::RemoveEvent(this);
			return;
		}
		currTime;
		pGobj->pBody->SetActive(true);

		pGobj->pBody->ApplyAngularImpulse(10, true);

		//float nextEventTime = 5 * (rand() % 10) / 10.0f + 1.0f;
		//TimerMan::AddEvent(currTime + nextEventTime, new Jump(pGobj));
		TimerMan::RemoveEvent(this);
	}


};



#endif