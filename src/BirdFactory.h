#ifndef BIRD_FACTORY_H
#define BIRD_FACTORY_H

#include "GameObjectName.h"
#include "ImageName.h"
#include "Rect.h"
#include "GameSortBucket.h"
#include "Bird.h"

class BirdFactory
{
public:
	static Bird *Create(GameObjectName::Name gObjName, ImageName::Name imageName, Rect rect);

};


#endif