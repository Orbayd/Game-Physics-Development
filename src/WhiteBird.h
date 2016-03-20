#ifndef WHITEBIRD_H
#define WHITEBIRD_H
#include "Bird.h"
class WhiteBird : public Bird
{
public:
	WhiteBird() = delete;

	virtual ~WhiteBird();

	static WhiteBird *Create(GameObjectName::Name gObjName, ImageName::Name imageName, Rect rect);

	virtual void AddBlinkEvent()override;
	virtual void PlayWarCry()override;
	virtual void ChangeSpriteToFly()override;
	virtual void ChangeSpriteToDeath()override;
private:
	void CreateBody(b2Vec2 center, float scale, float angle, b2Vec2 linVel, float angleVel);
	WhiteBird(GameObjectName::Name name, GraphicsObject_Sprite *pSprite, GameSortBucket *pSort);
};


#endif