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
	this->rotate = 0.001f;


}

void Diamond::Update()
{
	model_matrix = glm::rotate(model_matrix, rotate, glm::vec3(1.0, 0.5, 0.1));

}

void Diamond::Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix)
{

	glUseProgram(program);
	glUniformMatrix4fv(glGetUniformLocation(program, "model_matrix"),1, false, &model_matrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "view_matrix"), 1, false, &view_matrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "projection_matrix"), 1, false, &projection_matrix[0][0]);
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}