#ifndef BLUEBIRD_H
#define BLUEBIRD_H
#include "Bird.h"
class BlueBird : public Bird
{
public:
	BlueBird() = delete;

	virtual ~BlueBird();

	static BlueBird *Create(GameObjectName::Name gObjName, ImageName::Name imageName, Rect rect);
	static BlueBird *Copy(GameObjectName::Name gObjName,  GameObject2D * const copy, b2Vec2 pos);

	virtual void AddBlinkEvent()override;
	virtual void PlayWarCry()override;
	virtual void ChangeSpriteToFly()override;
	virtual void ChangeSpriteToDeath()override;
private:
	void CreateBody(b2Vec2 center, float scale, float angle, b2Vec2 linVel, float angleVel);
	BlueBird(GameObjectName::Name name, GraphicsObject_Sprite *pSprite, GameSortBucket *pSort);
};


#endif