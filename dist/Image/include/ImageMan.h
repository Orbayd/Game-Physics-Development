#ifndef IMAGE_MAN_H
#define IMAGE_MAN_H

#include "Image.h"
#include "ImageNode.h"

// Singleton
class ImageMan
{
public:
	static void addImage(ImageName::Name _imageName, TextName::Name _textName, Rect _rect);
	static Image *find(const ImageName::Name _name);

private:  // methods

	static ImageMan *privGetInstance();
	ImageMan();

	// helper private methods
	void privAddToFront(ImageNodeLink *node, ImageNodeLink *&head);

private:  // add

	ImageNodeLink *active;
};

#endif