#include "PrimitiveHelper.h"

PrimitiveHelper* PrimitiveHelper::m_pHelperInstance;

PrimitiveHelper* PrimitiveHelper::GetInstance()
{
	if (m_pHelperInstance == nullptr)
		m_pHelperInstance = new PrimitiveHelper();

	return m_pHelperInstance;
}

std::vector<Vertex> PrimitiveHelper::Cube()
{
	vector<Vertex> vertices;
	GLfloat _tempVerts[] = {
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

		-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

		 0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		 0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		 0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		 0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
		 0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		 0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		 0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		 0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		 0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f
	};

	int count = sizeof(_tempVerts) / sizeof(GLfloat);
	
	for (int i = 0; i < count; i+=5)
	{
		Vertex _temp = Vertex();
		_temp.Position = glm::vec3(_tempVerts[i], _tempVerts[i + 1], _tempVerts[i + 2]);
		_temp.Normal = glm::vec3(0, 0, 0);
		_temp.TextureCoords = glm::vec2(_tempVerts[i + 3], _tempVerts[i + 4]);

		vertices.push_back(_temp);
	}

	return vertices;
}
std::vector<Vertex> PrimitiveHelper::Quad()
{
	vector<Vertex> vertices;

	//Used with DRAW_ARRAY, No indices supplied.
	GLfloat _tempVerts[] = {
		0.5f, 0.5f, 1.0f, 1.0f, //Top right
	    0.5f,-0.5f, 1.0f, 0.0f, //Bottom right
	   -0.5f,-0.5f, 0.0f, 0.0f, //Bottom left

	   	0.5f, 0.5f, 1.0f, 1.0f, //Top right
	   -0.5f,-0.5f, 0.0f, 0.0f, //Bottom left
	   -0.5f, 0.5f, 0.0f, 1.0f //Top Left
	};

	int count = sizeof(_tempVerts) / sizeof(GLfloat);
	
	for (int i = 0; i < count; i+=4)
	{
		Vertex _temp = Vertex();
		_temp.Position = glm::vec3(_tempVerts[i], _tempVerts[i + 1], 0);
		_temp.Normal = glm::vec3(0, 0, 0);
		_temp.TextureCoords = glm::vec2(_tempVerts[i + 2], _tempVerts[i + 3]);

		vertices.push_back(_temp);
	}

	return vertices;
}




