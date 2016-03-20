#ifndef EVENT_NAME_H
#define EVENT_NAME_H
#include "EnumBase.h"

struct EventName : public EnumBase
{
	EventName(EventName::Name n)
	{
		this->value = n;
	}
	enum Name
	{
		BLINK = 0x90000,
		DEFAULT,
		JUMP,
		OINK,

	};


};
#endif