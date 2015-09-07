#include "stdafx.h"
#include "InitGLEW.h"
using namespace BasicEngine::Core::Init;

void Init_GLEW::Init()
{

	glewExperimental = true;
	
	if (glewInit() == GLEW_OK)
	{
		std::cout << "GLEW: Initialized" << std::endl;
	}
	int s = glGetError();
	if (glewIsSupported("GL_VERSION_4_4"))
	{
		std::cout << "GLEW GL_VERSION_4_4 is 4.4\n ";
	}
	else
	{
		std::cout << " GLEW GL_VERSION_4_4 not supported\n ";
	}

}

