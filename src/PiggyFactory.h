#ifndef PIGGY_FACTORY_H
#define PIGGY_FACTORY_H

#include "GameObjectName.h"
#include "ImageName.h"
#include "Rect.h"
#include "GameSortBucket.h"
#include "Piggy.h"

class PiggyFactory
{
public:
	static Piggy *Create(GameObjectName::Name gObjName, ImageName::Name imageName, Rect rect);

};


#endif