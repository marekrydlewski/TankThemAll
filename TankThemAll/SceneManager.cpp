#include "stdafx.h"
#include "SceneManager.h"


SceneManager::SceneManager()
{
	glEnable(GL_DEPTH_TEST);

	shader_manager = new ShaderManager();
	shader_manager->CreateProgram("colorShader",
		"Shaders\\VertexShader.glsl",
		"Shaders\\FragmentShader.glsl");

	models_manager = new ModelsManager();
}

SceneManager::~SceneManager()
{
	delete shader_manager;
	delete models_manager;
}

void SceneManager::notifyBeginFrame()
{
	models_manager->Update();
}

void SceneManager::notifyDisplayFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	models_manager->Draw();
}

void SceneManager::notifyEndFrame()
{
	//nothing here for the moment
}

void SceneManager::notifyReshape(int width,
	int height,
	int previous_width,
	int previous_height)
{
	//nothing here for the moment 

}