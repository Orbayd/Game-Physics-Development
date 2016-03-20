#ifndef BACKGROUND_FACTORY_H
#define BACKGROUND_FACTORY_H

#include "GameObjectName.h"
#include "ImageName.h"
#include "Rect.h"
#include "GameSortBucket.h"
#include "BackGround.h"

class BackGroundFactory
{
public:
	static BackGround *Create(GameObjectName::Name gObjName, ImageName::Name imageName, Rect rect, const float rot = 0);

};


#endif





