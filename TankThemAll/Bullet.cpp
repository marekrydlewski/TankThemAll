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
	std::vector<GLuint>  indices = { 0, 1, 2,   //upfront
		3, 4, 5,   //upright
		6, 7, 8,  //upback
		9, 10, 11,  //upleft
		12, 13, 14,  //lowfront
		15, 16, 17, //lowright
		18, 19, 20, //lowleft
		21, 22, 23 }; //lowback

	//upfront
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 0, 1.0), glm::vec4(0, 0, 1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(0, 1.0, 0), glm::vec4(1, 0, 1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 0, 1.0), glm::vec4(1, 1, 1, 1)));

	//upright
	vertices.push_back(VertexFormat(glm::vec3(1.0, 0, 1.0), glm::vec4(1, 1, 1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(0, 1.0, 0), glm::vec4(1, 1, 0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 0, -1.0), glm::vec4(1, 0, 0, 1)));

	//upback
	vertices.push_back(VertexFormat(glm::vec3(1.0, 0, -1.0), glm::vec4(0, 0, 0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(0, 1.0, 0), glm::vec4(1, 0, 0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 0, -1.0), glm::vec4(1, 1, 0, 1)));

	//upleft
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 0, -1.0), glm::vec4(0, 0, 0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(0, 1.0, 0), glm::vec4(0, 0, 1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 0, 1.0), glm::vec4(0, 1, 1, 1)));

	//lowfront
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 0, 1.0), glm::vec4(1, 1, 1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(0, -1.0, 0), glm::vec4(1, 0, 0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 0, 1.0), glm::vec4(1, 0, 1, 1)));


	//lowright
	vertices.push_back(VertexFormat(glm::vec3(1.0, 0, 1.0), glm::vec4(0, 0, 0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(0, -1.0, 0), glm::vec4(1, 0, 0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 0, -1.0), glm::vec4(1, 0, 1, 1)));

	//lowback
	vertices.push_back(VertexFormat(glm::vec3(1.0, 0, -1.0), glm::vec4(0, 0, 0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(0, -1.0, 0), glm::vec4(0, 0, 1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 0, -1.0), glm::vec4(0, 1, 1, 1)));

	//lowleft
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 0, -1.0), glm::vec4(1, 1, 1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(0, -1.0, 0), glm::vec4(1, 1, 0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 0, 1.0), glm::vec4(1, 0, 0, 1)));

	calculateNormals(indices, vertices);

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
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::normal)));
	glBindVertexArray(0);
	this->vao = vao;
	this->vbos.push_back(vbo);
	this->vbos.push_back(ibo);

	this->model_matrix = glm::mat4(1.0);
	this->model_matrix = glm::rotate(this->model_matrix, 90.0f, glm::vec3(1, 0, 0));
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
		glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
	}

}

void Bullet::Spawn(const glm::mat4& bullet_model_matrix, GLfloat bullet_angle)
{
	isFired = true;
	angle = bullet_angle;
	model_matrix = bullet_model_matrix;
}

glm::vec3 Bullet::GetPosition()
{
	return glm::vec3(model_matrix[3][0], model_matrix[3][1], model_matrix[3][2]);

}

void Bullet::calculateNormals(std::vector<GLuint> indices, std::vector<VertexFormat> &vertices)
{
	std::vector<glm::vec3> uniqueVertices;
	std::map<int, glm::vec3> normals;

	for (int i = 0; i < indices.size(); i += 3)
	{
		glm::vec3 A, B, C;

		A = vertices[indices[i]].position;
		B = vertices[indices[i + 1]].position;
		C = vertices[indices[i + 2]].position;

		glm::vec3 faceNormal = glm::cross(A - B, C - B);

		for (int j = 0; j < 3; j++)
		{
			bool WasVertexUsed = false;
			int VertexIndex;
			for (int k = 0; k < uniqueVertices.size(); k++)
			{
				if (uniqueVertices[k] == vertices[indices[i + j]].position)
				{
					WasVertexUsed = true;
					VertexIndex = k;
				}
			}
			if (WasVertexUsed)
			{
				normals[VertexIndex] += faceNormal;
			}
			else
			{
				uniqueVertices.push_back(vertices[indices[i + j]].position);
				normals[uniqueVertices.size() - 1] = faceNormal;
			}
		}
	}

	for (auto &it : normals)
	{
		it.second = glm::normalize(it.second);
	}

	for (auto &v : vertices)
	{
		for (int i = 0; i < uniqueVertices.size(); i++)
		{
			if (v.position == uniqueVertices[i])
			{
				v.normal = normals[i];
				break;
			}
		}
	}
}