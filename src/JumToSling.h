#ifndef JUMPTOSLING_H
#define JUMPTOSLING_H

#include <assert.h>
#include "TimerEvent.h"
#include "Bird.h"
#include "TimerMan.h"
#include "Simulation.h"
#include "Level.h"
float initrot = 0.0f;
class JumpToSling : public TimerEvent
{
public:
	JumpToSling(GameObject2D *pObj, float _lastX, float _LastY, float  _firstX, float _firstY,float totalTime)
	{
		this->pGobj = pObj;
		this->eName = EventName::BLINK;

		lastPosX = _lastX;
		lastPosY = _LastY;

		firstPosX = _firstX;
		firstPosY = _firstY;

		totalTimeElapsed = totalTime;
	}

	virtual void Execute(float currTime) override
	{
		

		float PosX = firstPosX + totalTimeElapsed * (lastPosX - firstPosX);
		float PosY = 0;
		if (totalTimeElapsed <= 0.5f)
		{
			PosY = (4 * firstPosY - 4 * lastPosY - 9 * pGobj->origWidth)* totalTimeElapsed * (totalTimeElapsed - 1) + firstPosY;
			 pGobj->SetPosition(PosX, PosY);
			 TimerMan::AddEvent(currTime + Simulation::Instance()->getTimeStep(), 
				 new JumpToSling(pGobj, lastPosX, lastPosY, firstPosX, firstPosY, totalTimeElapsed + Simulation::Instance()->getTimeStep()));
		}
		else if (totalTimeElapsed > 0.5f && totalTimeElapsed < 1.0f)
		{
			PosY = (pGobj->origWidth * -9) * ((totalTimeElapsed - 0.5f) *(totalTimeElapsed - 0.5f)) + lastPosY + 2.25f * pGobj->origWidth;
			
			Bird *pBird = (Bird*)pGobj;
			
			pBird->SetPosition(PosX, PosY);
			initrot += 12.0f * DEGTORAD ;
			pBird->pBody->SetTransform(pBird->pBody->GetPosition(), initrot);
			
			TimerMan::AddEvent(currTime + Simulation::Instance()->getTimeStep(), 
			  new JumpToSling(pGobj, lastPosX, lastPosY, firstPosX, firstPosY, totalTimeElapsed + Simulation::Instance()->getTimeStep()));
		}
		
		TimerMan::RemoveEvent(this);


	}

	
	float lastPosX;
	float lastPosY;

	float firstPosX;
	float firstPosY;
	
	float totalTimeElapsed;


};



#endif