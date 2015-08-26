// TankThemAll.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ShaderLoader.h"
#include "GameModels.h"

using namespace std;

GLuint program;


void renderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 0.0, 0.0, 1.0);//clear red

	//use the created program
	glUseProgram(program);

	//draw 3 vertices as triangles
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glutSwapBuffers();
}

void Init()
{

	glEnable(GL_DEPTH_TEST);

	//load and compile shaders
	ShaderLoader shaderLoader;
	program = shaderLoader.CreateProgram("Shaders\\VertexShader.glsl",
		"Shaders\\FragmentShader.glsl");
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

int _tmain(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Drawing my first triangle");
	glewInit();

	Init();

	// register callbacks
	glutDisplayFunc(renderScene);
	glutMainLoop();
	glDeleteProgram(program);
	return 0;
}
