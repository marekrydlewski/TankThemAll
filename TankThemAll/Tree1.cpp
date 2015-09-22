#include "stdafx.h"
#include "Tree1.h"

using namespace BasicEngine;
using namespace Rendering;
using namespace Models;

Tree1::Tree1()
{
}


Tree1::~Tree1()
{
}

void Tree1::Create(GLchar *path, GLfloat offsetX, GLfloat offsetZ)
{
	this->ImportedModel::Create(path);
	for (auto &m : meshes)
	{
		m->model_matrix = glm::translate(glm::scale(m->model_matrix,glm::vec3(1.4,1.4,1.4)), glm::vec3(offsetX, -0.2, offsetZ));
	}
}