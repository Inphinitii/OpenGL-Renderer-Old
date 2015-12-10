#include <glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>
#include "TyrUtility.h"
#include "IOManager.h"
#include <math.h>

#define GLM_FORCE_RADIANS

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
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

GLuint VAO, program;
//Player models
Model* player1, *player2;

//Ball
Model* _ballObject;

//Background/Environment models
Model *backgroundSquare, *divider;

glm::mat4 myTrans;
glm::vec3 p1Position, p2Position, ballPosition, ballVelocity;

float movement = 7;
bool player1Hit, player2Hit;
int player1Score, player2Score;
double dTime, currentTime, lastTime;

double fakeTime = 1.0f/60.0f;

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
		currentTime = glfwGetTime();
		dTime = currentTime - lastTime;
		lastTime = currentTime;

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

	myTrans = glm::mat4();


	/* Player 1 */
	player1->Position(p1Position);
	myTrans = player1->Translate() * player1->Scale();
	player1->TransformMatrix(myTrans);

	/* Player 2 */
	player2->Position(p2Position);
	myTrans = player2->Translate() * player2->Scale();
	player2->TransformMatrix(myTrans);

	/* Ball Object*/
	ballPosition += ballVelocity *(float)fakeTime * (float)fakeTime;

	_ballObject->Position(ballPosition);
	myTrans = _ballObject->Translate() * _ballObject->Scale();
	_ballObject->TransformMatrix(myTrans);

#pragma region Ball -> World Collision

	if (ballPosition.x > (backgroundSquare->ReturnScale().x / 2) - 0.05f || ballPosition.x < -(backgroundSquare->ReturnScale().x / 2) + 0.05f) //FUDGE FACTOR
	{
		ballVelocity.x *= -1;
	}

	if (ballPosition.y > (backgroundSquare->ReturnScale().y / 2) - 0.05f) //FUDGE FACTOR
	{
		ballVelocity.y *= -1;
	}

	if (ballPosition.y < -(backgroundSquare->ReturnScale().y / 2) + 0.05f)
	{
		//Whoever last touched the ball receives the point
		if (player1Hit)
			player1Score++;
		else if (player2Hit)
			player2Score++;

		//Print out the score to the consoles
		printf("Player 1: %i , Player 2: %i \n", player1Score, player2Score);

		//Reset the ball object to the center of the stage
		_ballObject->Position(ballPosition = glm::vec3(0.0f, 0.0f, 0.0f));

		//Set a random velocity for the ball
		ballVelocity = glm::vec3(rand() % 2 - 4 / 1.5f,
								 rand() % 2 / 1.5f,
								 0.0f);

		//Regenerate a Y value if it's outside of this threshold
		while (ballVelocity.y < 0.2f && ballVelocity.y > -0.2f)
		{
			ballVelocity.y = rand() % 2 / 1.5f;
		}
		
		//Reset the flags for the next round
		player1Hit = false;
		player2Hit = false;
	}

#pragma endregion

#pragma region Ball -> Paddle Collision

	if (ballPosition.y <= (player1->ReturnPosition().y + player1->ReturnScale().y /2) &&
		ballPosition.y >= (player1->ReturnPosition().y - player1->ReturnScale().y/2))
	{
		if (ballPosition.x > (player1->ReturnPosition().x - player1->ReturnScale().x / 2) && 
			ballPosition.x < (player1->ReturnPosition().x + player1->ReturnScale().x / 2))
		{
			player1Hit = true;
			player2Hit = false;
			ballVelocity.y *= -1;
		}

		if (ballPosition.x > (player2->ReturnPosition().x - player2->ReturnScale().x / 2) && 
			ballPosition.x < (player2->ReturnPosition().x + player2->ReturnScale().x / 2))
		{
			player2Hit = true;
			player1Hit = false;
			ballVelocity.y *= -1;
		}
	}
#pragma endregion





}

void Init(GLFWwindow* window)
{
	float ratio;
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float)height;
	glEnable(GL_DEPTH_TEST);
	player1Hit = false;
	//Wireframe mode for testing
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	GenerateShader();

	/* Player 1 Creation & Initialization */
	player1 = new Model(
			  new MeshRenderer(
			  new MeshData(VAO, PrimitiveHelper::GetInstance()->Quad()),
			  ShaderCache::GetInstance()->ReturnShader("program")));

	player1->DefaultColor(glm::vec4(0.2f, 0.2f, 0.5f, 1.0f));
	player1->Scale(glm::vec3(0.75f, 0.10f, 0.25f));
	p1Position = glm::vec3(-1.5f, -0.5f, 0.0f); //Initial positions


	/* Player 2 Creation & Initialization */
	player2 = new Model(*player1);
	player2->DefaultColor(glm::vec4(0.7f, 0.2f, 0.5f, 1.0f));
	p2Position = glm::vec3(1.5f, -0.5f, 0.0f); //Initial positions


	/* Ball object Creation & Initialization */
	_ballObject = new Model(*player1);
	_ballObject->DefaultColor(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	_ballObject->Scale(glm::vec3(0.1f, 0.1f, 0.1f));
	_ballObject->Position(ballPosition = glm::vec3(1.0f, 0.0f, 0.0f));
	 ballVelocity = glm::vec3(rand() % 2 -4 / 1.5f,
							  rand() % 2 / 1.5f,
							  0.0f);

	 //If the ball is at too low of a Y velocity, redo it until it's outside the range
	 while (ballVelocity.y < 0.2f && ballVelocity.y > -0.2f)
	 {
		 ballVelocity.y = rand() % 2 / 1.5f;
	 }

	//Create a new square and scale it up to be our background
	backgroundSquare = new Model(*player1);
	backgroundSquare->DefaultColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	backgroundSquare->Scale(glm::vec3(5.0f, 3.75f, 5.0f));

	divider = new Model(*player1);
	divider->DefaultColor(glm::vec4(0.5f, 0.3f, 0.2f, 0.1f));
	divider->Scale(glm::vec3(0.1f, 3.75f, 0.0f));

	/* Since these objects are not dynamic, set their variables in the initialization method */
	/* Background */
	myTrans = backgroundSquare->Scale();
	backgroundSquare->TransformMatrix(myTrans);

	/* Divider */
	divider->Position(glm::vec3(0.0f, 0.0f, 0.0f));
	myTrans = divider->Translate() * divider->Scale();
	divider->TransformMatrix(myTrans);
}
void Display(GLFWwindow* window)
{
	glClearColor(0.2f, 0.3f, 0.2f, 0.3f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	_ballObject->Draw(MeshRenderer::DRAW_ARRAY);
	divider->Draw(MeshRenderer::DRAW_ARRAY);
	player1->Draw(MeshRenderer::DRAW_ARRAY);
	player2->Draw(MeshRenderer::DRAW_ARRAY);
	backgroundSquare->Draw(MeshRenderer::DRAW_ARRAY);



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

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);

		//Player 1 controls
		if (key == GLFW_KEY_A)
		{
			if (player1->ReturnPosition().x >= -2.5f + (player1->ReturnScale().x/2) + 0.05f) //FUDGE FACTOR
				p1Position += glm::vec3(-movement * fakeTime, 0.0f, 0.0f);
		}

		if (key == GLFW_KEY_D)
		{
			if (player1->ReturnPosition().x <= 0.0f - player1->ReturnScale().x/2 - 0.15f)
				p1Position += glm::vec3(movement * fakeTime, 0.0f, 0.0f);
		}

		//Player 2 controls
		if (key == GLFW_KEY_LEFT)
		{
			if (player2->ReturnPosition().x >= 0.0f + player2->ReturnScale().x / 2 + 0.15f)
				p2Position += glm::vec3(-movement * fakeTime, 0.0f, 0.0f);
		}

		if (key == GLFW_KEY_RIGHT)
		{
			if (player2->ReturnPosition().x <= 2.5 - (player2->ReturnScale().x / 2) - 0.05f) //FUDGE FACTOR
				p2Position += glm::vec3(movement * fakeTime, 0.0f, 0.0f);
		}
	}


