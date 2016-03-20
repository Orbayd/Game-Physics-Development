#ifndef REDBIRD_H
#define REDBIRD_H
#include "Bird.h"



class RedBird : public Bird
{
public:
	RedBird() = delete;

	virtual ~RedBird();
	virtual void AddBlinkEvent()override;
	virtual void PlayWarCry()override;
	virtual void ChangeSpriteToFly()override;
	virtual void ChangeSpriteToDeath()override;

	static RedBird *Create(GameObjectName::Name gObjName, ImageName::Name imageName, Rect rect);
private:
	void CreateBody(b2Vec2 center, float scale, float angle, b2Vec2 linVel, float angleVel);
	RedBird(GameObjectName::Name name, GraphicsObject_Sprite *pSprite, GameSortBucket *pSort);

};


#endif