#include <glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>
#include "TyrUtility.h"
#include "IOManager.h"
#include <glm.hpp>
#include <gtx\transform.hpp>
#include <gtc\type_ptr.hpp>

#include "Model.h"
#include "ShaderCache.h"
#include "PrimitiveHelper.h"

static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

GLuint VAO, program;
Model* myModel, *myModel2;

glm::mat4 myTrans;
double dTime, currentTime, lastTime;

void Display(GLFWwindow* window);
void Init(GLFWwindow* window);
void OnIdle();
void GenerateShader();

int main(void)
{
	if (!glfwInit())
		exit(EXIT_FAILURE);


	GLFWwindow* window;
	glfwSetErrorCallback(error_callback);
	window = glfwCreateWindow(1024, 768, "OpenGL Test Bed", NULL, NULL);

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);

	glewExperimental = GL_TRUE;
	glewInit();

	Init(window);

	//Get the current time
	currentTime = glfwGetTime();
	lastTime = 0;

	while (!glfwWindowShouldClose(window))
	{
		OnIdle();
		Display(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void OnIdle()
{
	//Get the time and subtract it from the previous time to obtain Delta Time
	currentTime = glfwGetTime();
	dTime += currentTime - lastTime;
	lastTime = currentTime;

	myTrans = glm::mat4();

	//Translate and then rotate around a point
	myTrans = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f)) * 
			  glm::rotate(glm::mat4(1.0f), (float)dTime * 50, glm::vec3(0.0f, 0.0f, 1.0f));

	myModel->TransformMatrix(myTrans);

	myTrans = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, 0.0f)) * 
			  glm::rotate(glm::mat4(1.0f), (float)dTime * 50, glm::vec3(0.0f, 1.0f, 0.0f));

	myModel2->TransformMatrix(myTrans);

}

void Init(GLFWwindow* window)
{
	float ratio;
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float)height;
	glEnable(GL_DEPTH_TEST);

	//Wireframe mode for testing
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	GenerateShader();

	myModel = new Model(
			  new MeshRenderer(
			  new MeshData(VAO, PrimitiveHelper::GetInstance()->Cube()),
			  ShaderCache::GetInstance()->ReturnShader("program")));

	myModel2 = new Model(*myModel);

	myModel->Scale(glm::vec3(0.25, 0.25, 0.25));
	myModel2->Scale(glm::vec3(0.25, 0.25, 0.25));






}
void Display(GLFWwindow* window)
{
	glClearColor(0.2f, 0.3f, 0.2f, 0.3f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	myModel->Draw(MeshRenderer::DRAW_ARRAY);
	myModel2->Draw(MeshRenderer::DRAW_ARRAY);


	glfwSwapBuffers(window);

}

void GenerateShader()
{
	//GENERATE SHADER ---------------------------------
	std::vector<GLuint> shaderList;
	shaderList.push_back(TyrUtility::GetInstance()->CreateShader(GL_VERTEX_SHADER,
		IOManager::GetInstance()->FileToBuffer("vertexShader.vert")));

	shaderList.push_back(TyrUtility::GetInstance()->CreateShader(GL_FRAGMENT_SHADER,
		IOManager::GetInstance()->FileToBuffer("fragmentShader.frag")));

	program = TyrUtility::GetInstance()->CreateProgram(shaderList);
	ShaderCache::GetInstance()->AddShader("program", program);
	//GENERATE SHADER END-----------------------------
}


