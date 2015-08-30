#pragma once
#include "ContextInfo.h"
#include "FrameBufferInfo.h"
#include "WindowInfo.h"
#include "IListener.h"
#include "InitGLEW.h"
#include "DebugOutput.h"

class InitGLUT{

private:
	static IListener* listener;
	static WindowInfo windowInformation;

	static void idleCallback(void);
	static void displayCallback(void);
	static void reshapeCallback(int width, int height);
	static void closeCallback();

public:
	static void init(const WindowInfo& window,
		const ContextInfo& context,
		const FramebufferInfo& framebufferInfo);
	static void setListener(IListener*& iListener);

	static void run();//called from outside
	static void close();

	void enterFullscreen();
	void exitFullscreen();

	//used to print info about GL
	static void printOpenGLInfo(const WindowInfo& windowInfo,
		const ContextInfo& context);

};