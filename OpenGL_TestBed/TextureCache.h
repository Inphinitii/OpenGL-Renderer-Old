#include <string>
#include <map>
#include <glew.h>

#ifndef TEXTURECACHE_H
#define TEXTURECACHE_H

class TextureCache
{
public:
	static TextureCache* GetInstance();

	GLuint* ReturnTexture(std::string _textureName);
	void	AddTexture(std::string _textureName, GLuint* _texture);

private:
	TextureCache();
	~TextureCache();
	static TextureCache* m_textureCacheInstance;
	std::map<std::string, GLuint*> m_textureCache;
};

#endif