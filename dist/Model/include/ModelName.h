#ifndef MODEL_NAME
#define MODEL_NAME

#include "EnumBase.h"

struct ModelName : public EnumBase
{
	ModelName(ModelName::Name n)
	{
		this->value = n;
	}

	enum Name
	{
		Sprite = 0x60000,
		Circle,
		Box,
		Tri,
		NOT_INITIALIZED
	};
};

#endif