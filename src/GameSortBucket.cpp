#include "GameSortBucket.h"

#include "Box2D.h"
#include "GameObject.h"
#include "GraphicsObject_Sprite.h"
#include "Color.h"

GameSortBucket::GameSortBucket(GameObjectName::Name name)
{
	pGameSprite = 0;
	pBody = 0;

	this->name = name;
	this->debugColor = Color::Type::Red;

	this->drawSprite = false;
	this->drawDebug = false;
}

void GameSortBucket::PhysicsUpdate(b2Vec2 posInMeters, float angleInRadians)
{
	posInMeters;
	angleInRadians;
	assert(0);
}

GameSortBucket::~GameSortBucket()
{
}

GraphicsObject *GameSortBucket::getGraphicsObject()
{
	return this->pGameSprite;
}

void GameSortBucket::WorldUpdate(float currentTime)
{
	currentTime;
	this->pWorld->set(IDENTITY);
}

bool GameSortBucket::drawEnabled()
{
	return this->drawSprite;
}
