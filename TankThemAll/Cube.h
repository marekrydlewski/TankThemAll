#pragma once
#include<time.h>
#include<stdarg.h>
#include "Model.h"
class Cube :
	public Model
{
public:
	Cube();
	~Cube();

	void Create();
	virtual void Draw(const glm::mat4& projection_matrix,
		const glm::mat4& view_matrix); // no override here, other signature than in model
	virtual void Update() override final;

private:
	glm::vec3 rotation, rotation_speed;
	time_t timer;
};