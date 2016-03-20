#ifndef SEAT_H
#define SEAT_H

#include "GameObject2D.h"
#include "GameSortBucket.h"

class Seat : public GameObject2D
{
public:
	// Create
	Seat(GameObjectName::Name name, GraphicsObject_Sprite *pSprite, GameSortBucket *pSort);
	~Seat();
	void SetAnchorPoint(const float x, const float y);
	void Join(GameObject2D* pbird);
	float anchorX;
	float anchorY;
private:

	Seat();

};

#endif