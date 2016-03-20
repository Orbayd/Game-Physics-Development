#ifndef DEFAULT_H
#define DEFAULT_H

#include <assert.h>
#include "TimerEvent.h"
#include "Bird.h"



class Default : public TimerEvent
{
public:
	Default(GameObject2D *_pObj, ImageName::Name _iName, ImageName::Name _iBlink)
	{
		this->pGobj = _pObj;
		iName = _iName;
		iBlink = _iBlink;
		this->eName = EventName::BLINK;
	}

	virtual void Execute(float currTime) override;

	
private:
	ImageName::Name iName;
	ImageName::Name iBlink;

};

#endif