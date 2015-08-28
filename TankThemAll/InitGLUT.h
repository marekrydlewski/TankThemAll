#pragma once
#include "ContextInfo.h"
#include "FrameBufferInfo.h"
#include "WindowInfo.h"
#include "InitGLEW.h"

class InitGLUT{

public:
	static void init(const WindowInfo& window,
		const ContextInfo& context,
		const FramebufferInfo& framebufferInfo);

public:
	static void run();//called from outside
	static void close();

	void enterFullscreen();
	void exitFullscreen();

	//used to print info about GL
	static void printOpenGLInfo(const WindowInfo& windowInfo,
		const ContextInfo& context);
private:
	static void idleCallback(void);
	static void displayCallback(void);
	static void reshapeCallback(int width, int height);
	static void closeCallback();
};