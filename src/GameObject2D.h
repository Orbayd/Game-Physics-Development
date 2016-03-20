#ifndef GAME_OBJECT_2D_H
#define GAME_OBJECT_2D_H

#include "Box2D.h"
#include "GameObject.h"
#include "GraphicsObject_Sprite.h"
#include "GraphicsObject_Quad.h"
#include "GraphicsObject_Circle.h"

#include "Color.h"


class GameObject2D : public GameObject
{
public:
	// Many different options	
	GameObject2D(GameObjectName::Name name, GraphicsObject_Quad *graphicsObject);
	GameObject2D(GameObjectName::Name name, GraphicsObject_Sprite *graphicsObject);
	GameObject2D(GameObjectName::Name name, GraphicsObject_Circle  *graphicsObject);
	GameObject2D(GameObjectName::Name name);

	
	virtual EnumBase getName() override;
	virtual ~GameObject2D() override;
	virtual bool HasBody()override;

	virtual GraphicsObject *getGraphicsObject() override;
	virtual void WorldUpdate(float currentTime) override;
	virtual bool drawEnabled() override;

	virtual void AddDamage(float normalImpulse);
	virtual float PendingLifeLeft();
	
	void SetPosition(const float x, const float y);
	void PhysicsUpdate(b2Vec2 posInMeters, float angleInRadians);
public:
	// Movement Variables
	float damage;
	float pendingDamage;
	float maxDamage;

	float scaleX;
	float scaleY;
	float posX;
	float posY;
	float angle;

	// Original Sizes
	float origWidth;
	float origHeight;

	// Graphics Sprite
	GraphicsObject *pGameSprite;
	b2Body *pBody;
	GameObjectName::Name name;
	Color::Type debugColor;
	
	ImageName::Name iName;

	bool drawSprite;
	bool drawDebug;


};


#endif