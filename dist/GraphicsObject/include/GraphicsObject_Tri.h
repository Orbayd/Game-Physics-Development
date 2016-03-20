#ifndef GRAPHICS_OBJECT_TRI_H
#define GRAPHICS_OBJECT_TRI_H

#include "GraphicsObject.h"
#include "Vect2D.h"
#include "Color.h"

class GraphicsObject_Tri : public GraphicsObject
{
public:
	GraphicsObject_Tri( Vect2D *vertList);
	virtual ~GraphicsObject_Tri() override;
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
	Color::Type debugColor;

	Vect2D originVerts[8];

private:
	GraphicsObject_Tri() = delete;
};
#endif