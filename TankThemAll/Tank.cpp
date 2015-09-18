#include "stdafx.h"
#include "Tank.h"
using namespace BasicEngine;
using namespace Rendering;
using namespace Models;


Tank::Tank()
{
	tank_model_matrix = glm::mat4(1.0f);
}


Tank::~Tank()
{
}


glm::mat4 Tank::GetTankMatrix()
{
	return tank_model_matrix;
}