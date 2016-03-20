#include "ParticleEmitter.h"


 
ParticleEmitter::ParticleEmitter(GameObjectName::Name _gObjName, Rect _rect, GameSortBucket *_pSort, ImageName::Name _imageName0)
{
	this->gObjName = _gObjName;
	this->imageName0 = _imageName0;
	this->rect = _rect;
	this->pSort = _pSort;
}



