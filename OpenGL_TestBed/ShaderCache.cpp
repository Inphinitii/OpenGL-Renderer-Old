#include "ShaderCache.h"

ShaderCache* ShaderCache::m_shaderCacheInstance;

ShaderCache::ShaderCache(){}
ShaderCache::~ShaderCache(){}

ShaderCache* ShaderCache::GetInstance()
{
	if (m_shaderCacheInstance == nullptr)
		m_shaderCacheInstance = new ShaderCache();

	return m_shaderCacheInstance;
}

void ShaderCache::AddShader(std::string _fileName, GLuint _shader)
{
	if (m_shaderCache.find(_fileName) == m_shaderCache.end())
		m_shaderCache.insert(std::pair<std::string, GLuint>(_fileName, _shader));
}

GLuint* ShaderCache::ReturnShader(std::string _fileName)
{
	if (m_shaderCache.find(_fileName) == m_shaderCache.end())
		return nullptr;
	
	return &m_shaderCache.at(_fileName);
}