// TankThemAll.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GLFW/glfw3.h>

using namespace std;


int _tmain(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 500);//optional
	glutInitWindowSize(800, 600); //optional
	glutCreateWindow("OpenGL First Window");
 
	glutMainLoop();
 
	return 0;
}

