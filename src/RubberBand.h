#ifndef RUBBERBAND_H
#define RUBBERBAND_H

#include "GameObject2D.h"
#include "GameSortBucket.h"

class RubberBand : public GameObject2D
{
public:
	// Create
	RubberBand(GameObjectName::Name name, GraphicsObject_Quad *pQuad, GameSortBucket *pSort);
	~RubberBand();
	void SetAnchorPoint(const float x, const float y);
	float anchorX;
	float anchorY;
private:
	
	RubberBand();
	
};

#endif