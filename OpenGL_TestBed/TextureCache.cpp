#include "TextureCache.h"

TextureCache* TextureCache::m_textureCacheInstance;

TextureCache::TextureCache(){}
TextureCache::~TextureCache(){}

TextureCache* TextureCache::GetInstance()
{
	if (m_textureCacheInstance == nullptr)
		m_textureCacheInstance = new TextureCache();

	return m_textureCacheInstance;
}

void TextureCache::AddTexture(std::string _fileName, GLuint* _texture)
{
	if (m_textureCache.find(_fileName) == m_textureCache.end())
		m_textureCache.insert(std::pair<std::string, GLuint*>(_fileName, _texture));
}

GLuint* TextureCache::ReturnTexture(std::string _fileName)
{
	if (m_textureCache.find(_fileName) == m_textureCache.end())
		return nullptr;

	return m_textureCache.at(_fileName);
}