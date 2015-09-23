#include "stdafx.h"
#include "Bullets.h"

using namespace BasicEngine;
using namespace Rendering;
using namespace Models;

Bullets::Bullets()
{
}


Bullets::~Bullets()
{

}



void Bullets::Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix)
{
	for (auto& bullet : listOfBullets)
	{
		bullet->Draw(projection_matrix, view_matrix);
	}

}

void Bullets::Update()
{
	for (auto& bullet : listOfBullets)
	{
		bullet->Update();
	}
}

void Bullets::AddBullet(const glm::mat4& bullet_model_matrix, GLfloat angle)
{
	Bullet* bullet = new Bullet();
	bullet->SetProgram(this->program);
	bullet->Create();
	bullet->Spawn(bullet_model_matrix, angle);

	this->listOfBullets.push_back(bullet);
}


void Bullets::Create()
{

}