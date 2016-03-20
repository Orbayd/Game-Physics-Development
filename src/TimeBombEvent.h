#include <assert.h>
#include "TimerEvent.h"
#include "Bird.h"
#include "TimerMan.h"
#include "Simulation.h"
class TimeBomb : public TimerEvent
{
public:
	TimeBomb(GameObject2D *pObj,float _time)
	{
		this->pGobj = pObj;
		this->eName = EventName::JUMP;
		this->totalTimeElapsed = _time;
	}

	virtual void Execute(float currTime) override
	{
		if (pGobj == 0)
		{
			TimerMan::RemoveEvent(this);
			return;
		}
		
		Bird* pbird = (Bird*)pGobj;
		if (totalTimeElapsed >= 0.0f && totalTimeElapsed < 0.04f)
		{
			pbird->getGraphicsObject()->SetImage(ImageName::BlackBirdBombPhase_1);
			TimerMan::AddEvent(currTime + Simulation::Instance()->getTimeStep(), new TimeBomb(pbird, totalTimeElapsed + Simulation::Instance()->getTimeStep()));
		}
		else if (totalTimeElapsed >= 0.04f && totalTimeElapsed < 0.08f)
		{
			pbird->getGraphicsObject()->SetImage(ImageName::BlackBirdBombPhase_2);
			TimerMan::AddEvent(currTime + Simulation::Instance()->getTimeStep(), new TimeBomb(pbird, totalTimeElapsed + Simulation::Instance()->getTimeStep()));
		}
		else if (totalTimeElapsed >= 0.08 && totalTimeElapsed < 0.012f)
		{
			pbird->getGraphicsObject()->SetImage(ImageName::BlackBirdBombPhase_3);
			TimerMan::AddEvent(currTime + Simulation::Instance()->getTimeStep(), new TimeBomb(pbird, totalTimeElapsed + Simulation::Instance()->getTimeStep()));
		}
		else if (totalTimeElapsed >= 0.012f)
		{
			pbird->ExecuteAbility();

		}
		TimerMan::RemoveEvent(this);
	}
	float totalTimeElapsed;

};
