#ifndef GRAPHICS_OBJECT_SPRITE_H
#define GRAPHICS_OBJECT_SPRITE_H

#include "GraphicsObject.h"
#include "Image.h"

class GraphicsObject_Sprite : public GraphicsObject
{
public:
	GraphicsObject_Sprite(ImageName::Name name, Rect rect);
	virtual ~GraphicsObject_Sprite() override;

	virtual void SetImage(ImageName::Name name) override;

	// Rendermaterial contract
	virtual void SetState() override;
	virtual void SetDataGPU() override;	
	virtual void Draw() override;
	virtual void RestoreState() override;

// data:  place uniform instancing here
	
	//GLuint textureID;
	Image	*pImage;
	Matrix	*pMatrix_uv;
	Matrix  *pMatrix_orig;

	float origWidth; 
	float origHeight; 

	float origPosX;
	float origPosY;
};
#endif