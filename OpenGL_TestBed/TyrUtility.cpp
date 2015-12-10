#include "TyrUtility.h"

TyrUtility* TyrUtility::m_ShaderHelperSingleton;

TyrUtility* TyrUtility::GetInstance()
{
	if (m_ShaderHelperSingleton == nullptr)
		m_ShaderHelperSingleton = new TyrUtility();

	return m_ShaderHelperSingleton;
}
TyrUtility::TyrUtility()
{
}
TyrUtility::~TyrUtility()
{
}


#pragma region Shader Creation

/* Courtesy of Arc Synthesis */
GLuint TyrUtility::CreateShader(GLenum _shaderType, const std::string &_shaderFile)
{
	GLuint _shader = glCreateShader(_shaderType); //Create an empty shader
	const char *_fileData = _shaderFile.c_str();

	glShaderSource(_shader, 1, &_fileData, NULL); //Populate the internal shader with the external shader file data
	glCompileShader(_shader); //Compile the shader

	GLint status;
	glGetShaderiv(_shader, GL_COMPILE_STATUS, &status);

	//ERROR OUTPUT BEGIN --------------------------------------------------------------------
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(_shader, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(_shader, infoLogLength, NULL, strInfoLog);

		const char *strShaderType = NULL;

		switch (_shaderType)
		{
			case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
			case GL_GEOMETRY_SHADER: strShaderType = "geometry"; break;
			case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
		}

		fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
		delete[] strInfoLog;
	}
	//ERROR OUTPUT END------------------------------------------------------------------------

	return _shader;

}

GLuint TyrUtility::CreateProgram(const std::vector<GLuint> &_shaderList)
{
	GLuint _program = glCreateProgram(); //Create an empty program and store its address into this GLuint

	for (size_t i = 0; i < _shaderList.size(); i++)
		glAttachShader(_program, _shaderList[i]);

	glLinkProgram(_program);

	GLint _status;
	glGetProgramiv(_program, GL_LINK_STATUS, &_status); //Obtain the linking status of the program

	if (_status == GL_FALSE)
	{
		GLint infoLogLength; 
		glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(_program, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}

	for (size_t i = 0; i < _shaderList.size(); i++)
		glDetachShader(_program, _shaderList[i]);

	return _program;

}

#pragma endregion 

#pragma region Texture Creation

#pragma endregion 