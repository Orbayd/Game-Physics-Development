#ifndef YELLOWBIRD_H
#define YELLOWBIRD_H
#include "Bird.h"
class YellowBird : public Bird
{
public:
	YellowBird() = delete;

	virtual ~YellowBird();

	static YellowBird *Create(GameObjectName::Name gObjName, ImageName::Name imageName, Rect rect);

	virtual void AddBlinkEvent()override;
	virtual void PlayWarCry()override;
	virtual void ChangeSpriteToFly()override;
	virtual void ChangeSpriteToDeath()override;
private:
	void CreateBody(b2Vec2 center, float scale, float angle, b2Vec2 linVel, float angleVel);
	YellowBird(GameObjectName::Name name, GraphicsObject_Sprite *pSprite, GameSortBucket *pSort);
};


#endif