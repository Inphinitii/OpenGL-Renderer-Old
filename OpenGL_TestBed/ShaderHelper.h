#pragma once
#include <glew.h>
#include <string>
#include <vector>

#ifndef SHADERHELPER_H
#define SHADERHELPER_H

class ShaderHelper
{
private:
	static ShaderHelper* m_ShaderHelperSingleton;
	ShaderHelper();
	~ShaderHelper();
public:
	static ShaderHelper* GetInstance();
	GLuint CreateShader(GLenum _shaderType, const std::string &_shaderFile);
	GLuint CreateProgram(const std::vector<GLuint> &_shaderList);
};

#endif

