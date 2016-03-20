#ifndef BLINK_H
#define BLINK_H

#include <assert.h>
#include "TimerEvent.h"
#include "Bird.h"
#include "TimerMan.h"

#include "Default.h"
class Blink : public TimerEvent
{
public:
	Blink(GameObject2D *pObj, ImageName::Name _iDefault, ImageName::Name _iName)
	{
		this->pGobj = pObj;
		iName = _iName;
		iDefault = _iDefault;
		this->eName = EventName::BLINK;
	}

	virtual void Execute(float currTime) override
	{
		if (pGobj == 0)
		{
			TimerMan::RemoveEvent(this);
			return;
		}
		currTime;
		//ImageName::Name oldImage = ((GraphicsObject_Sprite *)pGobj->getGraphicsObject())->pImage->name;
		pGobj->getGraphicsObject()->SetImage(iName);
		

		TimerMan::AddEvent(currTime + 0.250f, new Default(pGobj, iDefault,iName));
		TimerMan::RemoveEvent(this);
	}

	
	ImageName::Name iName;
	ImageName::Name iDefault;
};

#endif
