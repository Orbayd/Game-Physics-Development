#ifndef BLOCK_FACTORY_H
#define BLOCK_FACTORY_H

#include "GameObjectName.h"
#include "ImageName.h"
#include "Rect.h"
#include "GameSortBucket.h"
#include "Block.h"

class BlockFactory
{
public:
	static Block *Create(GameObjectName::Name gObjName, ImageName::Name imageName, Rect rect,const float rot = 0, b2BodyType type = b2BodyType::b2_dynamicBody);
	
private :
	static void CreateBody(Block  *  pBlock, b2BodyType type, const  float density, const  float friction, const float restution);
};


#endif