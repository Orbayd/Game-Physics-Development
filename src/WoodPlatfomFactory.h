#ifndef WOOD_PLATFORM_FACTORY_H
#define WOOD_PLATFORM_FACTORY_H

#include "GameObjectName.h"
#include "ImageName.h"
#include "Rect.h"
#include "GameSortBucket.h"
#include "WoodPlatform.h"

class PlatformFactory
{
public:
	static WoodPlatform *Create(GameObjectName::Name gObjName, ImageName::Name imageName, Rect rect, const float rot = 0, b2BodyType type = b2BodyType::b2_staticBody);

};


#endif