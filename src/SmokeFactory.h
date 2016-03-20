#ifndef SMOKE_FACTORY_H
#define SMOKE_FACTORY_H
#include "Image.h"
//Forward Decleration //
class Smoke;
class GameSortBucket;
class SmokeFactory
{
public:
	static Smoke* Create(ImageName::Name imageName, Rect rect,GameSortBucket *pSort);
	

private:
	
};




#endif