#pragma once

#include "Model.h"
#include <time.h>
#include <stdarg.h>

using namespace BasicEngine::Rendering::Models;
class Bullet: public Model
{
public:
	Bullet();
	~Bullet();

	bool isFired;
	void Create();
	virtual void Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix) override final;
	virtual void Update() override final;

private:
	GLfloat rotate;
};
