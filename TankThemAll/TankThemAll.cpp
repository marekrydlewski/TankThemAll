// TankThemAll.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "InitGLUT.h"
#include "SceneManager.h"
int main(int argc, char **argv)
{
	WindowInfo window(std::string("TankThemAll"),
		400, 200,//position
		800, 600, //size
		true);//reshape

	ContextInfo context(4, 5, true);
	FramebufferInfo frameBufferInfo(true, true, true, true);
	InitGLUT::init(window, context, frameBufferInfo);

	IListener* scene = new SceneManager();
	InitGLUT::setListener(scene);

	InitGLUT::run();

	delete scene;
	return 0;
}