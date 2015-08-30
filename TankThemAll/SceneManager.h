#pragma once
#include "IListener.h"
#include "ShaderManager.h"
#include "ModelsManager.h"

class SceneManager :
	public IListener
{
public:
	SceneManager();
	~SceneManager();

	virtual void notifyBeginFrame();
	virtual void notifyDisplayFrame();
	virtual void notifyEndFrame();
	virtual void notifyReshape(int width,
		int height,
		int previous_width,
		int previous_height);
private:
	ShaderManager* shader_manager;
	ModelsManager* models_manager;
	glm::mat4 projection_matrix;
	glm::mat4 view_matrix;
};

