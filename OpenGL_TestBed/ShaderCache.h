#include <string>
#include <map>
#include <glew.h>

#ifndef SHADERCACHE_H
#define SHADERCACHE_H

class ShaderCache
{
public:
	static ShaderCache* GetInstance();

	GLuint* ReturnShader(std::string _shaderName);
	void	AddShader(std::string _shaderName, GLuint _shader);

private:
	ShaderCache();
	~ShaderCache();
	static ShaderCache* m_shaderCacheInstance;
	std::map<std::string, GLuint> m_shaderCache;
};

#endif