#ifndef THREAD_MILL_H
#define THREAD_MILL_H
#include "GameObject2D.h"
class GameSortBucket;
class ThreadMill : public GameObject2D
{
public:
	
	~ThreadMill();
	ThreadMill(GameObjectName::Name name, GraphicsObject_Sprite *pSprite, GameSortBucket *pSort);
	static ThreadMill *Create(GameObjectName::Name gObjName, Vect &pos, float rotatePos);
private:
	ThreadMill();
};






#endif