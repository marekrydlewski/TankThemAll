#include "stdafx.h"
#include "InitGLUT.h"

IListener* InitGLUT::listener = NULL;
WindowInfo InitGLUT::windowInformation;

void InitGLUT::init(const WindowInfo& windowInfo,
	const ContextInfo& contextInfo,
	const FramebufferInfo& framebufferInfo)
{	

	windowInformation = windowInfo;//initialize

	//we need to create these fake arguments
	int fakeargc = 1;
	char *fakeargv[] = { "fake", NULL };
	glutInit(&fakeargc, fakeargv);

	if (contextInfo.core)
	{
		glutInitContextVersion(contextInfo.major_version,
			contextInfo.minor_version);
		glutInitContextProfile(GLUT_CORE_PROFILE);
	}
	else
	{
		// version doesn't matter
		// in Compatibility mode
		glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	}

	glutInitDisplayMode(framebufferInfo.flags);
	glutInitWindowPosition(windowInfo.position_x,
		windowInfo.position_y);
	glutInitWindowSize(windowInfo.width, windowInfo.height);

	glutCreateWindow(windowInfo.name.c_str());

	std::cout << "GLUT:initialized" << std::endl;
	//these callbacks are used for rendering
	glutIdleFunc(idleCallback);
	glutCloseFunc(closeCallback);
	glutDisplayFunc(displayCallback);
	glutReshapeFunc(reshapeCallback);

	//init GLEW, this can be called in main.cpp
	InitGLEW::Init();

	//cleanup
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,
		GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	//our method to display some info. Needs contextInfo and windowinfo
	printOpenGLInfo(windowInfo, contextInfo);

}

//starts the rendering Loop
void InitGLUT::run()
{
	std::cout << "GLUT:\t Start Running " << std::endl;
	glutMainLoop();
}

void InitGLUT::printOpenGLInfo(const WindowInfo& windowInfo, const ContextInfo& contextInfo){

	const unsigned char* renderer = glGetString(GL_RENDERER);
	const unsigned char* vendor = glGetString(GL_VENDOR);
	const unsigned char* version = glGetString(GL_VERSION);

	std::cout << "*******************************************************************************" << std::endl;

	std::cout << "GLUT:\tVendor : " << vendor << std::endl;
	std::cout << "GLUT:\tRenderer : " << renderer << std::endl;
	std::cout << "GLUT:\tOpenGl version: " << version << std::endl;
	std::cout << "GLUT:\tInitial window is '" << windowInfo.name << "', with dimensions (" << windowInfo.width
		<< "X" << windowInfo.height;
	std::cout << ") starts at (" << windowInfo.position_x << "X" << windowInfo.position_y;
	std::cout << ") and " << ((windowInfo.isReshapable) ? "is" : "is not ") << " redimensionable" << std::endl;
	std::cout << "GLUT:\tInitial Framebuffer contains double buffers for" << std::endl;

	std::cout << "GLUT:\t OpenGL context is " << contextInfo.major_version << "." << contextInfo.minor_version;
	std::cout << " and profile is " << ((contextInfo.core) ? "core" : "compatibility") << std::endl;

	std::cout << "*****************************************************************" << std::endl;
}


void InitGLUT::close()
{
	std::cout << "GLUT:\t Finished" << std::endl;
	glutLeaveMainLoop();
}

void InitGLUT::idleCallback(void)
{
	//do nothing, just redisplay
	glutPostRedisplay();
}

void InitGLUT::displayCallback()
{
	if (listener)
	{
		listener->notifyBeginFrame();
		listener->notifyDisplayFrame();

		glutSwapBuffers();

		listener->notifyEndFrame();
	}
}

void InitGLUT::reshapeCallback(int width, int height)
{
	if (windowInformation.isReshapable == true)
	{
		if (listener)
		{
			listener->notifyReshape(width,
				height,
				windowInformation.width,
				windowInformation.height);
		}
		windowInformation.width = width;
		windowInformation.height = height;
	}
}

void InitGLUT::closeCallback()
{
	close();
}

void InitGLUT::enterFullscreen()
{
	glutFullScreen();
}

void InitGLUT::exitFullscreen()
{
	glutLeaveFullScreen();
}

void InitGLUT::setListener(IListener*& iListener)
{
	listener = iListener;
}