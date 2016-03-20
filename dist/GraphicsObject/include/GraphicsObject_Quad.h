#ifndef GRAPHICS_OBJECT_QUAD_H
#define GRAPHICS_OBJECT_QUAD_H

#include "GraphicsObject.h"
#include "Image.h"
#include "Vect2D.h"

class GraphicsObject_Quad : public GraphicsObject
{
public:
	GraphicsObject_Quad(ImageName::Name name,Vect2D *vertList);
	virtual ~GraphicsObject_Quad() override;
	
	virtual void SetImage(ImageName::Name) override;


	// Rendermaterial contract
	virtual void SetState() override;
	virtual void SetDataGPU() override;
	virtual void Draw() override;
	virtual void RestoreState() override;

	// data:  place uniform instancing here

	void getVects(Vect *outVects);
	void setVects(Vect *inVects);

	//GLuint textureID;
	Image	*pImage;
	Matrix	*pMatrix_uv;
	Matrix  *pMatrix_orig;

	Vect2D	vertsList[4];
};

#endif