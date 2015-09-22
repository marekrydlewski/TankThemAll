#include "stdafx.h"
#include "Skybox.h"
using namespace BasicEngine;
using namespace Rendering;
using namespace Models;

Skybox::Skybox()
{
}


Skybox::~Skybox()
{
}

void Skybox::Create(BasicEngine::Managers::Scene_Manager *sceneManager)
{
	_sceneManager = sceneManager;
}

void Skybox::Destroy()
{

}

void Skybox::Draw()
{
	//abstract
}

void Skybox::Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix)
{

}

const GLuint Skybox::GetTexture(std::string textureName) const
{
	return 0;
}

GLuint Skybox::GetVao() const
{
	return 0;
}

const std::vector<GLuint> Skybox::GetVbos() const
{
	std::vector<GLuint> nullvec;
	return nullvec;
}

void Skybox::SetProgram(GLuint program)
{

}

void Skybox::SetTexture(std::string textureName, GLuint texture)
{

}

void Skybox::Update()
{

}