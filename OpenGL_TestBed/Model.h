#pragma once

#include "MeshRenderer.h"
#include <glm.hpp>
#include <gtx\transform.hpp>
#include <gtc\type_ptr.hpp>

#ifndef MODEL_H
#define MODEL_H

class Model
{
private:
	vector<MeshRenderer*> m_meshRenderer;
	int m_meshCounter;

	GLuint	  m_modelLocation, m_projectionLocation, m_viewLocation, m_colorLocation, m_matrixBlock;
	glm::mat4 m_modelMatrix;

	glm::vec3 m_modelPosition;
	glm::vec3 m_modelScale;
	glm::vec3 m_modelRotationAxis;
	float m_rotationAngle;
	glm::vec4 m_modelColor;

	glm::mat4 m_projectionMatrix; //MOVE THIS TO AN APPROPRIATE CLASS LATER
	glm::mat4 m_viewMatrix;


public:
	Model(MeshRenderer* _renderer);
	~Model();
	Model(const Model &_temp){ *this = _temp; }

	void UpdateShader();
	void Draw(MeshRenderer::DRAW_MODE _mode);

	void TransformMatrix(glm::mat4 _mat4);
	void DefaultColor(glm::vec4 _vec4);

	//Set position, scale, and rotation
	void Position(glm::vec3 _vec3);
	void Scale	 (glm::vec3 _vec3);
	void Rotation(glm::vec3 _axis, float _angle);

	//Return position, scale, rotation angle if necessary
	glm::vec3 ReturnPosition()	{ return m_modelPosition; }
	glm::vec3 ReturnScale()		{ return m_modelScale; 	}
	float	  ReturnRotAngle()	{ return m_rotationAngle; }

	//For use in setting up the Transformation Matrix
	glm::mat4 Translate() { return glm::translate	(glm::mat4(1.0f), m_modelPosition); }
	glm::mat4 Rotate()	  { return glm::rotate		(glm::mat4(1.0f), m_rotationAngle, m_modelRotationAxis); }
	glm::mat4 Scale()	  { return glm::scale		(glm::mat4(1.0f), m_modelScale); }






};

#endif
