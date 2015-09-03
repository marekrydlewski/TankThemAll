#pragma once

#include "Model.h"
#include <time.h>
#include <stdarg.h>

using namespace BasicEngine::Rendering::Models;

class Diamond :
	public Model
{
public:
	Diamond();
	virtual ~Diamond();

	void Create();
	virtual void Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix) override final;
	virtual void Update() override final;
	
private:
private:
	glm::vec3 rotation, rotation_speed;
	time_t timer;
};

