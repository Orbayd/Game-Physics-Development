#ifndef TIMER_MAN_H
#define TIMER_MAN_H

#include "TimerEvent.h"
class GameObject2D;
class TimerMan
{
public:
	static void Create();
	static void AddEvent(float TimeInSec, TimerEvent *pEvent);
	static void RemoveEvent(TimerEvent *pEvent);
	static void Update();
	static void CleanObjectEvents(GameObject2D *pObj);
	static void CleanObjectEvents(GameObject2D *pObj,EventName::Name eName);
private:
	static TimerMan *privInstance();
	void privAddToFront(TimerEvent *pEvent);
	void privRemoveFromList(TimerEvent *pEvent);
	TimerEvent *pActive;
	float currTime;
};



#endif