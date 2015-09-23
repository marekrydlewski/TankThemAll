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

	GLuint vao;
	GLuint vbo;
	GLuint ibo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	std::vector<VertexFormat> vertices;
	std::vector<GLuint>  indices = 
	{
		0,1,2,3
	};

	//front
	vertices.push_back(VertexFormat(glm::vec3(-65.0, 65.0, -65.0), glm::vec2(0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(65.0, 65.0, -65.0), glm::vec2(1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(65.0, -65.0, -65.0), glm::vec2(1, 0)));
	vertices.push_back(VertexFormat(glm::vec3(-65.0, -65.0, -65.0), glm::vec2(0, 0)));

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexFormat), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (GLvoid*)(offsetof(VertexFormat, VertexFormat::texture)));
	glBindVertexArray(0);
	this->vao = vao;
	this->vbos.push_back(vbo);
	this->vbos.push_back(ibo);

	//model matrix
	// puts 1.0 on the diagonal
	// all other components are 0.0
	this->model_matrix = glm::mat4(1.0);

	int texw, texh;
	SetTexture("skybox_front", TextureLoader::LoadTexture("textures\\siege_front.jpg", texw, texh));
	SetTexture("skybox_left", TextureLoader::LoadTexture("textures\\siege_left.jpg", texw, texh));
	SetTexture("skybox_right", TextureLoader::LoadTexture("textures\\siege_right.jpg", texw, texh));
	SetTexture("skybox_back", TextureLoader::LoadTexture("textures\\siege_back.jpg", texw, texh));
	SetTexture("skybox_top", TextureLoader::LoadTexture("textures\\siege_top.jpg", texw, texh));
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
	glUseProgram(program);
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(program, "skybox_texture"), 0);
	glBindTexture(GL_TEXTURE_2D, this->textures["skybox_front"]);
	glUniformMatrix4fv(glGetUniformLocation(program, "model_matrix"), 1, false, &model_matrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "view_matrix"), 1, false, &view_matrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "projection_matrix"), 1, false, &projection_matrix[0][0]);
	glDepthMask(0);
	glBindVertexArray(vao);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
	glDepthMask(1);
	model_matrix = glm::rotate(model_matrix, 90.0f, glm::vec3(0,1.0,0));
	glUniform1i(glGetUniformLocation(program, "skybox_texture"), 0);
	glBindTexture(GL_TEXTURE_2D, this->textures["skybox_left"]);
	glUniformMatrix4fv(glGetUniformLocation(program, "model_matrix"), 1, false, &model_matrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "view_matrix"), 1, false, &view_matrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "projection_matrix"), 1, false, &projection_matrix[0][0]);
	glDepthMask(0);
	glBindVertexArray(vao);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
	glDepthMask(1);
	model_matrix = glm::rotate(model_matrix, 90.0f, glm::vec3(0, 1.0, 0));
	glUniform1i(glGetUniformLocation(program, "skybox_texture"), 0);
	glBindTexture(GL_TEXTURE_2D, this->textures["skybox_back"]);
	glUniformMatrix4fv(glGetUniformLocation(program, "model_matrix"), 1, false, &model_matrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "view_matrix"), 1, false, &view_matrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "projection_matrix"), 1, false, &projection_matrix[0][0]);
	glDepthMask(0);
	glBindVertexArray(vao);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
	glDepthMask(1);
	model_matrix = glm::rotate(model_matrix, 90.0f, glm::vec3(0, 1.0, 0));
	glUniform1i(glGetUniformLocation(program, "skybox_texture"), 0);
	glBindTexture(GL_TEXTURE_2D, this->textures["skybox_right"]);
	glUniformMatrix4fv(glGetUniformLocation(program, "model_matrix"), 1, false, &model_matrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "view_matrix"), 1, false, &view_matrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "projection_matrix"), 1, false, &projection_matrix[0][0]);
	glDepthMask(0);
	glBindVertexArray(vao);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
	glDepthMask(1);
	model_matrix = glm::rotate(model_matrix, 90.0f, glm::vec3(0, 0, 1.0));
	glUniform1i(glGetUniformLocation(program, "skybox_texture"), 0);
	glBindTexture(GL_TEXTURE_2D, this->textures["skybox_top"]);
	glUniformMatrix4fv(glGetUniformLocation(program, "model_matrix"), 1, false, &model_matrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "view_matrix"), 1, false, &view_matrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "projection_matrix"), 1, false, &projection_matrix[0][0]);
	glDepthMask(0);
	glBindVertexArray(vao);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
	glDepthMask(1);

}

const GLuint Skybox::GetTexture(std::string textureName) const
{
	return textures.at(textureName);
}

GLuint Skybox::GetVao() const
{
	return vao;
}

const std::vector<GLuint> Skybox::GetVbos() const
{
	return vbos;
}

void Skybox::SetProgram(GLuint program)
{
	if (program == 0) return;
	this->program = program;
}

void Skybox::SetTexture(std::string textureName, GLuint texture)
{
	if (texture == 0) return;
	textures[textureName] = texture;
}

void Skybox::Update()
{
	model_matrix = glm::mat4(1.0);
	glm::vec3 camPos = _sceneManager->GetTankCameraPosition(false);
	model_matrix = glm::translate(model_matrix, camPos);
}