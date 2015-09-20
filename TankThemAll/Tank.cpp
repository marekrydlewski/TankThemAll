#include "stdafx.h"
#include "Tank.h"
using namespace BasicEngine;
using namespace Rendering;
using namespace Models;


Tank::Tank()
{
	tank_model_matrix = glm::mat4(1.0f);
	tank_model_position = glm::vec3(0.0f);
	tank_model_rotation = 0.0f;
}


Tank::~Tank()
{
}


glm::mat4 Tank::GetTankMatrix()
{
	return tank_model_matrix;
}

void Tank::TranslateMeshes()
{
	for (unsigned int i = 0; i < this->meshes.size(); i++)
	{
		this->meshes[i]->model_matrix = glm::rotate(this->meshes[i]->model_matrix, this->tank_model_rotation, glm::vec3(0, 1.0, 0));
		this->meshes[i]->model_matrix = glm::translate(this->meshes[i]->model_matrix, this->tank_model_position);

	}
	
}

void Tank::Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix)
{
	tank_model_matrix = glm::mat4(1.0f);
	tank_model_matrix = glm::rotate(tank_model_matrix, tank_model_rotation, glm::vec3(0.0f, 1.0f, 0.0f));
	tank_model_matrix = glm::translate(tank_model_matrix, tank_model_position);

	for (unsigned int i = 0; i < this->meshes.size(); i++)
	{
		this->meshes[i]->model_matrix = tank_model_matrix;
		this->meshes[i]->Draw(projection_matrix, view_matrix);
	}
}
