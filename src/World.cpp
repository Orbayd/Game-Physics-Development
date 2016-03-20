#include <assert.h>

#include "Box2D.h"
#include "World.h"


void World::Create(float gravityX, float gravityY)
{
	World *p = World::privGetInstance();
	assert(p);

	p->pWorld = new b2World(b2Vec2(gravityX, gravityY));
	assert(p->pWorld);
}

b2World *World::getWorld()
{
	World *p = World::privGetInstance();
	return p->pWorld;
}

World::World()
{
	this->pWorld = 0;
}

World *World::privGetInstance()
{
	// This is where its actually stored (BSS section)
	static World world;

	return &world;
}

void World::SettleLevel()
{
//	World * instance = World::privGetInstance();
	int velocityIterations = 6;
	int positionIternations = 2;
	World::getWorld()->Step(0.016f, velocityIterations, positionIternations);
	//instance->balanced = true;
}

bool World::isBalanced()
{
	World * instance = World::privGetInstance();

	return instance->balanced;

}
void World::setBalanced()
{
	World * instance = World::privGetInstance();
	instance->balanced = true;
}
