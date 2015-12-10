#include "MeshData.h"

MeshData::MeshData(GLuint &VAO, vector<Vertex> _vertices, vector<GLuint> _indices)
{
	m_vertices = _vertices;
	m_indices = _indices;
	m_VAO = &VAO;
	GenerateBuffers(VAO);
}

MeshData::MeshData(GLuint &VAO, vector<Vertex> _vertices)
{
	m_vertices = _vertices;
	m_VAO = &VAO;
	GenerateBuffers(VAO);
}


MeshData::~MeshData()
{
}

void MeshData::GenerateBuffers(GLuint &VAO)
{
	GLuint VBO, EBO;
	//Generate necessary buffer objects
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	//Vertex Information
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* m_vertices.size(), &m_vertices[0], GL_STATIC_DRAW);
	
	if (m_indices.size() > 0)
	{
		//Index Information
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)* m_indices.size(), &m_indices[0], GL_STATIC_DRAW);
	}
	

	//Shader Attribute Linkage START-----------------------------------------------------------------

		//Vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 
						 (GLvoid*)0);

		//Vertex Normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 
						 (GLvoid*)offsetof(Vertex, Normal));

		//Vertex Texture Coordinates
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), 
						 (GLvoid*)offsetof(Vertex, TextureCoords));


	//Shader Attribute Linkage END-------------------------------------------------------------------

	glBindVertexArray(0);
}
