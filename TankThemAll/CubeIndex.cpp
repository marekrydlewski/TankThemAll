#include "stdafx.h"
#include <iostream>
#include "CubeIndex.h"

using namespace BasicEngine;
using namespace Rendering;
using namespace Models;
using namespace std;

#define PI 3.14159265
GLfloat LightPosit[] = { 0.0, 10.0, 0.0 };
CubeIndex::CubeIndex()
{

	isDrawn = true;
}


CubeIndex::~CubeIndex()
{
}

void CubeIndex::Create(GLfloat offsetX, GLfloat offsetY, GLfloat offsetZ)
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
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, 1.0), glm::vec2(0, 0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, 1.0), glm::vec2(0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, 1.0), glm::vec2(1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, 1.0), glm::vec2(1, 0)));

	//right
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, 1.0), glm::vec2(0, 0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, -1.0), glm::vec2(0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, -1.0), glm::vec2(1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, 1.0), glm::vec2(1, 0)));

	//back
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, -1.0), glm::vec2(0, 0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, -1.0), glm::vec2(0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, -1.0), glm::vec2(1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, -1.0), glm::vec2(1, 0)));

	//left
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, -1.0), glm::vec2(0, 0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, 1.0), glm::vec2(0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, 1.0), glm::vec2(1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, -1.0), glm::vec2(1, 0)));

	//upper
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, 1.0), glm::vec2(0, 0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, 1.0), glm::vec2(0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, -1.0), glm::vec2(1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, -1.0), glm::vec2(1, 0)));


	//bottom
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, -1.0), glm::vec2(0, 0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, -1.0), glm::vec2(0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, 1.0), glm::vec2(1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, 1.0), glm::vec2(1, 0)));

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
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::texture)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::normal)));
	glBindVertexArray(0);
	this->vao = vao;
	this->vbos.push_back(vbo);
	this->vbos.push_back(ibo);

	this->model_matrix = glm::mat4(1.0);
	this->model_matrix = glm::translate(this->model_matrix, glm::vec3(0, 0.3, 0));
	this->model_matrix = glm::translate(this->model_matrix, glm::vec3(offsetX, offsetY, offsetZ));

	int texw, texh;
	SetTexture("wood", TextureLoader::LoadTexture("textures\\wooden_box.jpg", texw, texh));
}

void CubeIndex::Update()
{
	if (!isDrawn ) //&& model_matrix[3][1] > 0
	{
		this->model_matrix = glm::rotate(model_matrix, 0.1f, glm::vec3(0.1, 0, 0.1));
		this->model_matrix = glm::translate(model_matrix, glm::vec3(0.0f, -0.1f, 0.0f));

	}
}

void CubeIndex::Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix)
{

	//if (isDrawn)
	{
		glUseProgram(program);
		glActiveTexture(GL_TEXTURE0);
		GLint location = glGetUniformLocation(program, "texture_diffuse1");
		glUniform1i(location, 0);
		glBindTexture(GL_TEXTURE_2D, this->textures["wood"]);
		location = glGetUniformLocation(program, "light_source_1");
		glUniform3fv(location, 1, LightPosit);
		glUniformMatrix4fv(glGetUniformLocation(program, "model_matrix"), 1, false, &model_matrix[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(program, "view_matrix"), 1, false, &view_matrix[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(program, "projection_matrix"), 1, false, &projection_matrix[0][0]);
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}

}

void CubeIndex::calculateNormals(std::vector<GLuint> indices, std::vector<VertexFormat> &vertices)
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

bool CubeIndex::CheckCollision(glm::vec3 collider_position, GLfloat radius)
{
	if (isDrawn)
	{
		glm::vec3 cube_position = glm::vec3(model_matrix[3][0], model_matrix[3][1], model_matrix[3][2]);

		GLfloat x_collide, z_collide;
		GLfloat x_cube, z_cube;

		x_collide = collider_position.x;
		z_collide = collider_position.z;

		x_cube = cube_position.x;
		z_cube = cube_position.z;

		//cout << x_collide << " collide  " << z_collide << endl;
		//cout << x_cube << " cube" << z_cube << endl;
		auto rot = ((float)rand() / (float)RAND_MAX);
		rot /= 2;

		if ((((x_collide - x_cube)*(x_collide - x_cube)) +
			((z_collide - z_cube)*(z_collide - z_cube))) <= radius * radius)
		{
			isDrawn = false;
			return true;
		}
	}
	return false;
}


void CubeIndex::ActivateFall()
{

	isDrawn = false;

}