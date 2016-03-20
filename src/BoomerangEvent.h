#ifndef BOOMERANGEVENT_H
#define BOOMERANGEVENT_H

#include <assert.h>
#include "TimerEvent.h"
#include "Bird.h"
#include "TimerMan.h"


class BoomerangEvent : public TimerEvent
{
public:
	BoomerangEvent(GameObject2D *pObj ,float _velx)
	{
		this->pGobj = pObj;
		this->eName = EventName::BLINK;
		this->InitalvelX = _velx;
	}

	virtual void Execute(float currTime) override
	{
		if (pGobj == 0)
		{
			TimerMan::RemoveEvent(this);
			return;
		}
		currTime;
		float CurrentVX = pGobj->pBody->GetLinearVelocity().x;
		
		if (fabs(CurrentVX) < fabs(InitalvelX))
		{
			pGobj->pBody->ApplyForceToCenter(b2Vec2(InitalvelX * 4, 0), true);
			TimerMan::AddEvent(currTime + 0.0f, new BoomerangEvent(pGobj, InitalvelX));
		}
		else
		{
			
			//printf("");
		}
		
		//pGobj->getGraphicsObject()->SetImage(iName);


		
		TimerMan::RemoveEvent(this);
	}

	float InitalvelX;

};

#endif
