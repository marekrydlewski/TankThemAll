// TankThemAll.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"



using namespace std;


int _tmain(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 500);//optional
	glutInitWindowSize(800, 600); //optional
	glutCreateWindow("OpenGL First Window");
	cout << "fdsfdsffsd";
	glutMainLoop();

	return 0;
}
