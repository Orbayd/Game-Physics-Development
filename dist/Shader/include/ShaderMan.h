#ifndef SHADER_MAN_H
#define SHADER_MAN_H

#include "sb6.h"
#include "Shader.h"
#include "ShaderNode.h"

// Singleton
class ShaderMan
{
public:
	static void addShader(ShaderName::Name shaderName, const char * const shaderBaseFileName);
	//static void deleteShader();
	static Shader *findShader(const ShaderName::Name _name);

private:  // methods

	static ShaderMan *privGetInstance();
	ShaderMan();

	// helper private methods
	void privAddToFront(ShaderNodeLink *node, ShaderNodeLink *&head);

private:  // add

	ShaderNodeLink *active;
};

#endif