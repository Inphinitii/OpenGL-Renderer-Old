#pragma once
#include <glew.h>
#include <string>
#include <vector>

#ifndef TYRUTILITY_H
#define TYRUTILITY_H

class TyrUtility
{
private:
	static TyrUtility* m_ShaderHelperSingleton;
	TyrUtility();
	~TyrUtility();
public:
	static TyrUtility* GetInstance();

	//Shaders
	GLuint CreateShader(GLenum _shaderType, const std::string &_shaderFile);
	GLuint CreateProgram(const std::vector<GLuint> &_shaderList);

	//Textures
	GLuint CreateTexture(unsigned char* _fileName);
};

#endif

