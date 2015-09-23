#include "stdafx.h"
#include "Tree1.h"
#include <iostream>
#include <math.h>
using namespace BasicEngine;
using namespace Rendering;
using namespace Models;
using namespace std;

Tree1::Tree1()
{
	isDrawn = true;
}


Tree1::~Tree1()
{
}

void Tree1::Create(GLchar *path, GLfloat offsetX, GLfloat offsetZ)
{
	this->ImportedModel::Create(path);

	for (auto &m : meshes)
	{
			m->model_matrix = glm::translate(glm::scale(m->model_matrix, glm::vec3(1.4, 1.4, 1.4)), glm::vec3(offsetX, -0.2, offsetZ));
	}

}

void Tree1::CheckCollision(glm::vec3 collider_position, GLfloat radius)
{
	if (isDrawn)
	{
		glm::vec3 tree_position = glm::vec3(this->meshes[5]->model_matrix[3][0], this->meshes[5]->model_matrix[3][1], this->meshes[5]->model_matrix[3][2]);

		GLfloat x_collide, z_collide;
		GLfloat x_tree, z_tree;

		x_collide = collider_position.x;
		z_collide = collider_position.z;

		x_tree = tree_position.x;
		z_tree = tree_position.z;

		//cout << x_collide << " collide  " << z_collide << endl;
		//cout << x_tree << " tree" << z_tree << endl;
		auto rot = ((float)rand() / (float)RAND_MAX);
		rot /= 2;

		if ((((x_collide - x_tree)*(x_collide - x_tree)) +
			((z_collide - z_tree)*(z_collide - z_tree))) <= radius * radius)
		{
			isDrawn = false;
			for (unsigned int i = 0; i < 10; i++)
			{
				this->meshes[i]->model_matrix = glm::rotate(this->meshes[i]->model_matrix, 89.0f, glm::vec3(0.5 + rot, 0.5 + 0.3 * rot, 0.0));
			}
		}
	}
}


void Tree1::Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix)
{
	if (isDrawn)
		for (unsigned int i = 0; i < this->meshes.size(); i++)
		{
			this->meshes[i]->Draw(projection_matrix, view_matrix);
		}
	else
	{
		for (unsigned int i = 0; i < 10; i++)
		{
			this->meshes[i]->Draw(projection_matrix, view_matrix);
		}
	}
}
