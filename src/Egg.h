#ifndef EGG_H
#define EGG_H

#include "Particle.h"

class Egg : public Particle
{
public:
	// Create
	Egg(GameObjectName::Name name, GraphicsObject_Sprite *pSprite, GameSortBucket *pSort);
	Egg() = delete;
	virtual ~Egg(){}

	static Egg *Create(GameObjectName::Name gObjName, ImageName::Name imageName, Rect rect, GameSortBucket *pSort);
	virtual void CreateBody(b2Vec2 center, float scale, float angle, b2Vec2 linVel, float angleVel) override;
	virtual void WorldUpdate(float currentTime) override;
	
private:
	
};


#endif