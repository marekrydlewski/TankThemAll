#include "stdafx.h"
#include "Tank.h"
using namespace BasicEngine;
using namespace Rendering;
using namespace Models;


Tank::Tank()
{
	tank_model_matrix = glm::mat4(1.0f);
	tank_model_position = glm::vec3(0.0f);
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
		this->meshes[i]->model_matrix = glm::translate(this->meshes[i]->model_matrix, this->tank_model_position);
	}
	
}