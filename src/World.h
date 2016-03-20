#ifndef  WORLD_H
#define  WORLD_H

#include "Box2D.h"

class World
{
public:
	static void Create(float gravityX, float gravityY);

	static b2World *getWorld();
	static void SettleLevel();
	static bool isBalanced();
	static void setBalanced();
private:
	World();
	static World *privGetInstance();
	b2World *pWorld;
	bool  balanced;
};

#endif