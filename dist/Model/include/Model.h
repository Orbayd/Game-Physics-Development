#ifndef MODEL_H
#define MODEL_H

#include "ModelName.h"
#include "sb6.h"

class Model
{
public:
	Model();
	virtual ~Model();
	void Set(ModelName::Name name);
// Data
	int numVerts;
	int numTris;

	GLuint vao;
	GLuint vbo[2];

private:
	// load VAO
	virtual void privCreateVAO( const char * const modelFileName  ) = 0;

	ModelName::Name name;

	// prevent from copying
	Model( Model &copyModel );
	Model & operator = (Model &copyModel);
};

#endif