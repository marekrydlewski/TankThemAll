// TankThemAll.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ShaderLoader.h"
#include "GameModels.h"

using namespace std;

GameModels* gameModels;
GLuint program;

void renderScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.3, 0.3, 1.0);

	glBindVertexArray(gameModels->GetModel("triangle1"));
	glUseProgram(program);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glutSwapBuffers();
}

void closeCallback()
{

	std::cout << "GLUT:\t Finished" << std::endl;
	glutLeaveMainLoop();
}

void Init()
{

	glEnable(GL_DEPTH_TEST);

	gameModels = new GameModels();
	gameModels->CreateTriangleModel("triangle1");

	//load and compile shaders
	ShaderLoader shaderLoader;
	program = shaderLoader.CreateProgram("Shaders\\VertexShader.glsl",
		"Shaders\\FragmentShader.glsl");
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

int main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 500);
	glutInitWindowSize(800, 600);
	glutCreateWindow("OpenGL First Window");
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glewExperimental = true;
	glewInit();
	if (glewIsSupported("GL_VERSION_4_4")) //lower your version if 4.4 is not supported by your video card
	{
		std::cout << " OpenGL Version is 4.4\n ";
	}
	else
	{
		std::cout << "OpenGL 4.4 not supported\n ";
	}

	Init();
	// register callbacks
	glutDisplayFunc(renderScene);
	glutCloseFunc(closeCallback);

	glutMainLoop();

	delete gameModels;
	glDeleteProgram(program);
	return 0;
}
