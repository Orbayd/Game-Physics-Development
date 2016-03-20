#ifndef TEXTURE_NAME
#define TEXTURE_NAME

#include "EnumBase.h"

struct TextName : public EnumBase
{
	TextName(TextName::Name n)
	{
		this->value = n;
	}

	enum Name
	{
		AngryBirds = 0x40000,
		WoodBlocks,
		GlassBlocks,
		StoneBlocks,
		Platform,
		BackGround,
		AdditionalBlocks,
		Not_initialized
	};
};
#endif