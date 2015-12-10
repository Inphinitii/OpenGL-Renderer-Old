#pragma once
#include <glew.h>
#include "MeshData.h"
#include "ShaderCache.h"

#ifndef MESHRENDERER_H
#define MESHRENDERER_H

class MeshRenderer
{
private:
	MeshData*	m_rendererMeshData;
	GLuint*		m_rendererShader;




public:
	MeshRenderer();
	MeshRenderer(MeshData* _mesh, GLuint* _shader);
	MeshRenderer(MeshData* _mesh, GLuint* _shader, GLuint* _texture);
	MeshRenderer(const MeshRenderer& _other);
	~MeshRenderer();
	
	enum DRAW_MODE
	{
		DRAW_ELEMENTS,
		DRAW_ARRAY
	};

	void Draw(GLenum _mode, DRAW_MODE _mode2);

	GLuint* ReturnShader() { return m_rendererShader; }
	void EnableShader() { glUseProgram(*m_rendererShader); }
	void DisableShader() { glUseProgram(0); }



};

#endif

