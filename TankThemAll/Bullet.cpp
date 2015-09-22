#include "stdafx.h"
#include "Bullet.h"

using namespace BasicEngine;
using namespace Rendering;
using namespace Models;


#define PI 3.14159265

Bullet::Bullet()
{
	isFired = false;
}


Bullet::~Bullet()
{
}

void Bullet::Create()
{
	GLuint vao;
	GLuint vbo;
	GLuint ibo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	std::vector<VertexFormat> vertices;
	std::vector<unsigned int>  indices = { 0, 1, 2, 0, 2, 3,   //front
		4, 5, 6, 4, 6, 7,   //right
		8, 9, 10, 8, 10, 11,  //back
		12, 13, 14, 12, 14, 15,  //left
		16, 17, 18, 16, 18, 19,  //upper
		20, 21, 22, 20, 22, 23 }; //bottom
	//front
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, 1.0), glm::vec4(0, 0, 1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, 1.0), glm::vec4(1, 0, 1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, 1.0), glm::vec4(1, 1, 1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, 1.0), glm::vec4(0, 1, 1, 1)));

	//right
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, 1.0), glm::vec4(1, 1, 1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, -1.0), glm::vec4(1, 1, 0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, -1.0), glm::vec4(1, 0, 0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, 1.0), glm::vec4(1, 0, 1, 1)));

	//back
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, -1.0), glm::vec4(0, 0, 0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, -1.0), glm::vec4(1, 0, 0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, -1.0), glm::vec4(1, 1, 0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, -1.0), glm::vec4(0, 1, 0, 1)));

	//left
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, -1.0), glm::vec4(0, 0, 0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, 1.0), glm::vec4(0, 0, 1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, 1.0), glm::vec4(0, 1, 1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, -1.0), glm::vec4(0, 1, 0, 1)));

	//upper
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, 1.0), glm::vec4(1, 1, 1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, 1.0), glm::vec4(0, 1, 1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, -1.0), glm::vec4(0, 1, 0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, -1.0), glm::vec4(1, 1, 0, 1)));


	//bottom
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, -1.0), glm::vec4(0, 0, 0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, -1.0), glm::vec4(1, 0, 0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, 1.0), glm::vec4(1, 0, 1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, 1.0), glm::vec4(0, 0, 1, 1)));


	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexFormat), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::color)));
	glBindVertexArray(0);
	this->vao = vao;
	this->vbos.push_back(vbo);
	this->vbos.push_back(ibo);

	this->model_matrix = glm::mat4(1.0);
	//this->model_matrix = glm::translate(model_matrix, glm::vec3(1.0f, 1.0f, -1.5f));
	//this->model_matrix = glm::scale(model_matrix, glm::vec3(0.03f, 0.03f, 0.03f));
	//this->rotate = 0.01f;
}

void Bullet::Update()
{
	if (isFired)
	{
		model_matrix = glm::translate(model_matrix, 
			glm::rotateY(glm::vec3(0.7f, 0.0f, 0.0f),angle)
			);
	}
	
}

void Bullet::Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix)
{

	if (isFired)
	{
		glUseProgram(program);
		glUniformMatrix4fv(glGetUniformLocation(program, "model_matrix"), 1, false, &model_matrix[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(program, "view_matrix"), 1, false, &view_matrix[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(program, "projection_matrix"), 1, false, &projection_matrix[0][0]);
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}

}

void Bullet::Spawn(const glm::mat4& bullet_model_matrix, GLfloat bullet_angle)
{
	isFired = true;
	angle = bullet_angle;
	model_matrix = bullet_model_matrix;
}