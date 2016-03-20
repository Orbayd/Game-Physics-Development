#ifndef BLACKBIRD_H
#define BLACKBIRD_H
#include "Bird.h"
class BlackBird : public Bird
{
public:
	BlackBird() = delete;
	
	virtual ~BlackBird();
	
	static BlackBird *Create(GameObjectName::Name gObjName, ImageName::Name imageName, Rect rect);

	virtual void AddBlinkEvent()override;
	virtual void PlayWarCry()override;
	virtual void ChangeSpriteToFly()override;
	virtual void ChangeSpriteToDeath()override;
	virtual void DeadPhase()override;
private:
	void CreateBody(b2Vec2 center, float scale, float angle, b2Vec2 linVel, float angleVel) ;
	BlackBird(GameObjectName::Name name, GraphicsObject_Sprite *pSprite, GameSortBucket *pSort);
	bool deadFlag;
};


#endif