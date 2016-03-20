#ifndef GREEN_H
#define GREEN_H
#include "Bird.h"
class GreenBird : public Bird
{
public:
	GreenBird() = delete;

	virtual ~GreenBird();

	static GreenBird *Create(GameObjectName::Name gObjName, ImageName::Name imageName, Rect rect);
	virtual void AddBlinkEvent()override;
	virtual void PlayWarCry()override;
	virtual void ChangeSpriteToFly()override;
	virtual void ChangeSpriteToDeath()override;
private:
	void CreateBody(b2Vec2 center, float scale, float angle, b2Vec2 linVel, float angleVel);
	GreenBird(GameObjectName::Name name, GraphicsObject_Sprite *pSprite, GameSortBucket *pSort);
};


#endif