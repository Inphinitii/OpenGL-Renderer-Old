#pragma once
#include "glew.h"

#include "TyrUtility.h"
#include "IOManager.h"
#include "glm.hpp"


#ifndef MESHDATA_H
#define MESHDATA_H

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TextureCoords;
};

using namespace std;

class MeshData
{
private:
	GLuint* m_VAO;

	vector<Vertex> m_vertices;
	vector<GLuint> m_indices;

	void GenerateBuffers(GLuint &VAO);

public:
	MeshData(GLuint &VAO, vector<Vertex> _vertices, vector<GLuint> _indices);
	MeshData(GLuint &VAO, vector<Vertex> _vertices);

	~MeshData();

	int				IndexCount() { return m_indices.size(); }
	int				VertexCount(){ return m_vertices.size(); }

	vector<GLuint>* Indices()	{ return &m_indices; }
	vector<Vertex>* Vertices()	{ return &m_vertices; }
	GLuint* VAO()				{ return m_VAO; }



};

#endif

