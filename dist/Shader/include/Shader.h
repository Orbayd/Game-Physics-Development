#ifndef SHADER_H
#define SHADER_H

#include "sb6.h"
#include "ShaderName.h"

class Shader
{
public:
	Shader(ShaderName::Name shaderName, const char * const shaderBaseFileName);
	Shader();
	void Set(ShaderName::Name shaderName, const char * const shaderBaseFileName);
	void SetActive();
	GLint GetLocation(const char * uniformName);

private:
	bool privCreateShader(GLuint &programObject, const char * const shaderBaseFileName);
	bool privLoadNCompile(GLuint &shaderObject, const char * const shaderFileName, GLenum shader_type);

public:

	// data
	ShaderName::Name  name;
	GLuint		programObject;

};

#endif