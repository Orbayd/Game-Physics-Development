
#include "Default.h"
#include "TimerMan.h"
#include "Blink.h"

void Default::Execute(float currTime) 
{
	if (pGobj == 0)
	{
		TimerMan::RemoveEvent(this);
		return;
	}
	currTime;
	//ImageName::Name oldImage = ((GraphicsObject_Sprite *)pGobj->getGraphicsObject())->pImage->name;
	
	pGobj->getGraphicsObject()->SetImage(iName);
	float nextEventTime = 0.5f*(rand() % 10) / 10.0f + 0.2f;
	TimerMan::AddEvent(currTime + nextEventTime, new Blink(pGobj, iName, iBlink));
	TimerMan::RemoveEvent(this);
}