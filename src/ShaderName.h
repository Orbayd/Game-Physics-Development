#ifndef SHADER_NAME
#define SHADER_NAME

#include "EnumBase.h"

struct ShaderName : public EnumBase
{
	ShaderName(ShaderName::Name n)
	{
		this->value = n;
	}

	enum Name
	{
		COLOR_LIGHT = 0x50000,
		TEXTURE_SIMPLE,
		TEXTURE_POINT_LIGHT,
		SPRITE,
		SPRITE_LINE,
		SPRITE_TRI,
		SPRITE_QUAD,
		NOT_INITIALIZED
	};
};

#endif