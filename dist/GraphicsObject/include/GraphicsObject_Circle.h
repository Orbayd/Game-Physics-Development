#ifndef GRAPHICS_OBJECT_CIRCLE_H
#define GRAPHICS_OBJECT_CIRCLE_H

#include "GraphicsObject.h"
#include "Rect.h"
#include "Color.h"

class GraphicsObject_Circle : public GraphicsObject
{
public:
	GraphicsObject_Circle( Rect rect);
	virtual ~GraphicsObject_Circle() override;
	virtual void SetImage(ImageName::Name) override;

	// Rendermaterial contract
	virtual void SetState() override;
	virtual void SetDataGPU() override;
	virtual void Draw() override;
	virtual void RestoreState() override;

	// data:  place uniform instancing here
	Matrix  *pMatrix_orig;

	float origWidth;
	float origHeight;

	float origPosX;
	float origPosY;
	Color::Type debugColor;

private:
	GraphicsObject_Circle() = delete;
};
#endif