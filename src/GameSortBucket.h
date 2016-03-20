#ifndef GAME_SORT_BUCKET_H
#define GAME_SORT_BUCKET_H

#include "Box2D.h"
#include "GameObject.h"
#include "Color.h"

class GameSortBucket: public GameObject
{
public:
	// Many different options	
	GameSortBucket(GameObjectName::Name name);
	void PhysicsUpdate(b2Vec2 posInMeters, float angleInRadians);

	virtual EnumBase getName() override
	{
		return GameObjectName((EnumBase::Name)this->name);
	}
	virtual bool HasBody()override
	{
		return (pBody != 0);
	}
	virtual ~GameSortBucket() override;

	virtual GraphicsObject *getGraphicsObject() override;
	virtual void WorldUpdate(float currentTime) override;
	virtual bool drawEnabled() override;

public:
	GameSortBucket();

	// Graphics Sprite
	GraphicsObject *pGameSprite;
	b2Body *pBody;
	GameObjectName::Name name;
	Color::Type debugColor;
	float scale;
	
	bool drawSprite;
	bool drawDebug;

};

#endif