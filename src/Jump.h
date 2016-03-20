#ifndef JUMP_H
#define JUMP_H

#include <assert.h>
#include "TimerEvent.h"
#include "Bird.h"
#include "TimerMan.h"
#include "Simulation.h"
#include "Level.h"
class Jump : public TimerEvent
{
public:
	Jump(GameObject2D *pObj, float _LastY, float _firstY,float _angle, float totalTime)
	{
		this->pGobj = pObj;
		this->eName = EventName::JUMP;
		this->totalTimeElapsed = totalTime;
		this->lastPosY = _LastY;
		this->firstPosY = _firstY;
		this->angle = _angle;
	}

	virtual void Execute(float currTime) override
	{
		if (pGobj == 0)
		{
			TimerMan::RemoveEvent(this);
			return;
		}
		
		
		//float PosY = firstPosY + totalTimeElapsed * (lastPosY - firstPosY);
		//float PosY = (4 * firstPosY - 4 * lastPosY - 9 * pGobj->origWidth)* totalTimeElapsed * (totalTimeElapsed - 1) + firstPosY;
		//float PosY = firstPosY + totalTimeElapsed * (4 * lastPosY - 4 * firstPosY);
		if (totalTimeElapsed <= 1.0f)
		{

			if (totalTimeElapsed >= 0.30f && totalTimeElapsed <= 0.80f)
			{
				angle += (12.0f * DEGTORAD);	
			}

			float PosY = (4 * firstPosY - 4 * lastPosY - 7 * pGobj->origWidth)* totalTimeElapsed * (totalTimeElapsed - 1) + firstPosY;
			//float PosY = firstPosY + totalTimeElapsed * (4* lastPosY - 4* firstPosY);
			TimerMan::AddEvent(currTime + Simulation::Instance()->getTimeStep(), new Jump(pGobj, lastPosY, firstPosY,angle, totalTimeElapsed + Simulation::Instance()->getTimeStep()));
			pGobj->SetPosition(pGobj->posX, PosY);
			Bird* pBird = (Bird*)pGobj;
			pBird->pBody->SetTransform(pBird->pBody->GetPosition(), angle);
	
		}
		else 
		{
			float nextEventTime = 0.5f*(rand() % 10) / 10.0f + 2.0f;
			TimerMan::AddEvent(currTime + nextEventTime, new Jump(pGobj, firstPosY, lastPosY,0,0));
		}

		TimerMan::RemoveEvent(this);
	}

	
	float lastPosY;
	float firstPosY;
	float angle;
	float totalTimeElapsed;
};



#endif