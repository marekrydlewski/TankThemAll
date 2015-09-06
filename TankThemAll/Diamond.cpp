#include "stdafx.h"
#include "Diamond.h"

using namespace BasicEngine::Rendering;

#define PI 3.14159265

Diamond::Diamond()
{
}


Diamond::~Diamond()
{
}

void Diamond::Create()
{
	GLuint vao;
	GLuint vbo;
	GLuint ibo;

	time(&timer);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	std::vector<VertexFormat> vertices;
	std::vector<unsigned int>  indices = { 0, 1, 2,   //upfront
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

	rotation_speed = glm::vec3(1.0, 1.0, 0.5);
	rotation = glm::vec3(0.0, 0.0, 1.0);

}

void Diamond::Update()
{

}

void Diamond::Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix)
{
	rotation = 0.01f * rotation_speed + rotation;

	glm::vec3 rotation_sin = glm::vec3(rotation.x * PI / 180, rotation.y * PI / 180, rotation.z * PI / 180);

	glUseProgram(program);
	glUniform3f(glGetUniformLocation(program, "rotation"), rotation_sin.x, rotation_sin.y, rotation_sin.z);
	glUniformMatrix4fv(glGetUniformLocation(program, "view_matrix"), 1, false, &view_matrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "projection_matrix"), 1, false, &projection_matrix[0][0]);
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}