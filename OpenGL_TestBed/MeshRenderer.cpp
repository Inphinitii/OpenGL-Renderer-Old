#include "MeshRenderer.h"

MeshRenderer::MeshRenderer()
{

}

MeshRenderer::MeshRenderer(MeshData* _mesh, GLuint* _shader)
{
	m_rendererShader = _shader;
	m_rendererMeshData = _mesh;
}

MeshRenderer::MeshRenderer(MeshData* _mesh, GLuint* _shader, GLuint* _texture)
{
}


MeshRenderer::~MeshRenderer()
{
	delete[] m_rendererMeshData;
}

void MeshRenderer::Draw(GLenum _mode, DRAW_MODE _mode2)
{
	glUseProgram(*m_rendererShader);
	//Bind texture
	glBindVertexArray(*m_rendererMeshData->VAO());

	if (_mode2 == DRAW_MODE::DRAW_ELEMENTS)
	{
		glDrawElements(_mode, m_rendererMeshData->IndexCount() ,GL_UNSIGNED_INT, 0);

	}
	if (_mode2 == DRAW_MODE::DRAW_ARRAY)
	{
		glDrawArrays(GL_TRIANGLES, 0, m_rendererMeshData->VertexCount());
	}


	glBindVertexArray(0);
	//Unbind Texture
	glUseProgram(0);
}
