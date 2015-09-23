#include "stdafx.h"
#include "Skybox.h"
#include <SOIL.h>
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
		0,1,2,
		0,2,3,
		4,5,6,
		4,6,7,
		8,9,10,
		8,10,11,
		12,13,14,
		12,14,15,
		16,17,18,
		16,18,19,
		20,21,22,
		22,22,23
	};

	//front
	vertices.push_back(VertexFormat(glm::vec3(-65.0, 65.0, 65.0), glm::vec4(-1,1,1,1)));
	vertices.push_back(VertexFormat(glm::vec3(65.0, 65.0, 65.0), glm::vec4(1, 1,1,1)));
	vertices.push_back(VertexFormat(glm::vec3(65.0, -65.0, 65.0), glm::vec4(1, -1,1,1)));
	vertices.push_back(VertexFormat(glm::vec3(-65.0, -65.0, 65.0), glm::vec4(-1,-1,1,1)));

	//right
	vertices.push_back(VertexFormat(glm::vec3(65.0, 65.0, 65.0), glm::vec4(1,1,1,1)));
	vertices.push_back(VertexFormat(glm::vec3(65.0, 65.0, -65.0), glm::vec4(1, 1,-1,1)));
	vertices.push_back(VertexFormat(glm::vec3(65.0, -65.0, -65.0), glm::vec4(1, -1,-1,1)));
	vertices.push_back(VertexFormat(glm::vec3(65.0, -65.0, 65.0), glm::vec4(1,-1,1,1)));

	//left
	vertices.push_back(VertexFormat(glm::vec3(-65.0, 65.0, 65.0), glm::vec4(-1,1,1,1)));
	vertices.push_back(VertexFormat(glm::vec3(-65.0, 65.0, -65.0), glm::vec4(-1,1,-1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-65.0, -65.0, -65.0), glm::vec4(-1,-1,-1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-65.0, -65.0, 65.0), glm::vec4(-1,-1,1,1)));

	//back
	vertices.push_back(VertexFormat(glm::vec3(-65.0, 65.0, -65.0), glm::vec4(-1,1,-1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(65.0, 65.0, -65.0), glm::vec4(1, 1,-1,1)));
	vertices.push_back(VertexFormat(glm::vec3(65.0, -65.0, -65.0), glm::vec4(1, -1,-1,1)));
	vertices.push_back(VertexFormat(glm::vec3(-65.0, -65.0, -65.0), glm::vec4(-1,-1,-1,1)));

	//upper
	vertices.push_back(VertexFormat(glm::vec3(-65.0, 65.0, 65.0), glm::vec4(1,1,-1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(65.0, 65.0, 65.0), glm::vec4(-1, 1,-1,1)));
	vertices.push_back(VertexFormat(glm::vec3(65.0, 65.0, -65.0), glm::vec4(-1, 1,1,1)));
	vertices.push_back(VertexFormat(glm::vec3(-65.0, 65.0, -65.0), glm::vec4(1,1,1,1)));

	//lower
	vertices.push_back(VertexFormat(glm::vec3(-65.0, -65.0, 65.0), glm::vec4(-1, -1, 1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(65.0, -65.0, 65.0), glm::vec4(1, -1, 1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(65.0, -65.0, -65.0), glm::vec4(1, -1, -1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-65.0, -65.0, -65.0), glm::vec4(-1, -1, -1, 1)));

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexFormat), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (GLvoid*)(offsetof(VertexFormat, VertexFormat::color)));
	glBindVertexArray(0);
	this->vao = vao;
	this->vbos.push_back(vbo);
	this->vbos.push_back(ibo);

	//model matrix
	// puts 1.0 on the diagonal
	// all other components are 0.0
	this->model_matrix = glm::mat4(1.0);
	faces.push_back("textures\\FullMoonRight2048.png");
	faces.push_back("textures\\FullMoonLeft2048.png");
	faces.push_back("textures\\FullMoonUp2048.png");
	faces.push_back("textures\\FullMoonDown2048.png");
	faces.push_back("textures\\FullMoonBack2048.png");
	faces.push_back("textures\\FullMoonFront2048.png");
	SetTexture("cubemap", loadCubemap(faces));
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
	glDepthMask(0);
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(program, "skybox_texture"), 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->textures["cubemap"]);
	glUniformMatrix4fv(glGetUniformLocation(program, "model_matrix"), 1, false, &model_matrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "view_matrix"), 1, false, &view_matrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "projection_matrix"), 1, false, &projection_matrix[0][0]);
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
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

GLuint Skybox::loadCubemap(vector<const GLchar*> faces)
{
	GLuint textureID;
	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE0);

	int width, height;
	unsigned char* image;

	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	for (GLuint i = 0; i < faces.size(); i++)
	{
		image = SOIL_load_image(faces[i], &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
			GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image
			);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	return textureID;
}