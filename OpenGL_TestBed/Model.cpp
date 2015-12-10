#include "Model.h"


Model::Model(MeshRenderer* _renderer)
{
	m_meshCounter		 = 0;
	m_rotationAngle		 = 0;
	m_modelMatrix		 = glm::mat4();
	m_modelPosition		 = glm::vec3();
	m_modelRotationAxis	 = glm::vec3();
	m_modelScale		 = glm::vec3();
	m_modelLocation		 = glGetUniformLocation(*_renderer->ReturnShader(), "model"); //Default transform in default vert shader
	m_projectionLocation = glGetUniformLocation(*_renderer->ReturnShader(), "projection");
	m_viewLocation		 = glGetUniformLocation(*_renderer->ReturnShader(), "view");
	m_colorLocation		 = glGetUniformLocation(*_renderer->ReturnShader(), "color");
	m_meshRenderer.push_back(_renderer);
	m_meshCounter++;

	m_projectionMatrix = glm::perspective(45.0f, 1024.0f / 768.0f, 0.1f, 1000.0f);
	m_viewMatrix = glm::translate(m_viewMatrix, glm::vec3(0.0f, 0.0f, -5.0f));

}


Model::~Model()
{
	m_meshRenderer.erase(m_meshRenderer.begin(), m_meshRenderer.end());
}

void Model::UpdateShader()
{
	for (int i = 0; i < m_meshRenderer.size(); i++)
	{
		m_meshRenderer[i]->EnableShader();
		glUniformMatrix4fv(m_modelLocation, 1, GL_FALSE, glm::value_ptr(m_modelMatrix));
		glUniformMatrix4fv(m_projectionLocation, 1, GL_FALSE, glm::value_ptr(m_projectionMatrix));
		glUniformMatrix4fv(m_viewLocation, 1, GL_FALSE, glm::value_ptr(m_viewMatrix));
		glUniform4fv	  (m_colorLocation, 1, glm::value_ptr(m_modelColor));
		m_meshRenderer[i]->DisableShader();
	}

}

void Model::Draw(MeshRenderer::DRAW_MODE _mode)
{
	for (int i = 0; i < m_meshRenderer.size(); i++)
	{
		UpdateShader();
		m_meshRenderer[i]->EnableShader();
		m_meshRenderer[i]->Draw(GL_TRIANGLES, _mode);
		m_meshRenderer[i]->DisableShader();
	}
}

void Model::Position(glm::vec3 _vec3)
{
	m_modelPosition = _vec3;
}

void Model::Scale(glm::vec3 _vec3)
{
	m_modelScale = _vec3;
}

void Model::Rotation(glm::vec3 _vec3, float _angle)
{
	m_modelRotationAxis = _vec3;
	m_rotationAngle		= _angle;
}

void Model::TransformMatrix(glm::mat4 _mat4)
{
	m_modelMatrix = _mat4;
}

void Model::DefaultColor(glm::vec4 _vec4)
{
	m_modelColor = _vec4;
}



