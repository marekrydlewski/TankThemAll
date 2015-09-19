#include "stdafx.h"
#include "Mesh.h"


using namespace BasicEngine::Rendering;

Mesh::Mesh(std::vector<VertexFormat> vertices, std::vector<GLuint> indices, std::vector<TextureWrap> textures)
{
	this->Create(vertices, indices, textures);
}

Mesh::~Mesh()
{
}

void Mesh::Create(std::vector<VertexFormat> vertices, std::vector<GLuint> indices, std::vector<TextureWrap> textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	this->setupMesh();
}

void Mesh::Update()
{
	//model_matrix = glm::rotate(model_matrix, 0.01f, glm::vec3(0.0, 1.0, 0.0));
}

void Mesh::Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix)
{
	GLuint diffuseNr = 1;
	GLuint specularNr = 1;
	glUseProgram(program);
	for (int i = 0; i < this->textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // Activate proper texture unit before binding
		// Retrieve texture number (the N in diffuse_textureN)
		std::stringstream ss;
		std::string number;
		std::string name = this->textures[i].type;
		if (name == "texture_diffuse")
			ss << diffuseNr++; // Transfer GLuint to stream
		else if (name == "texture_specular")
			ss << specularNr++; // Transfer GLuint to stream
		number = ss.str();

		GLint location = glGetUniformLocation(program, (name + number).c_str());
		glUniform1i(location, i);
		glBindTexture(GL_TEXTURE_2D, this->textures[i].id);
	}
	// Draw mesh
	glUniformMatrix4fv(glGetUniformLocation(program, "model_matrix"), 1, false, &model_matrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "view_matrix"), 1, false, &view_matrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "projection_matrix"), 1, false, &projection_matrix[0][0]);
	glBindVertexArray(this->vao);
	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::setupMesh()
{
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(VertexFormat),
		&this->vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint),
		&this->indices[0], GL_STATIC_DRAW);

	// Vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat),
		(GLvoid*)0);

	// Vertex Texture Coords
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat),
		(GLvoid*)offsetof(VertexFormat, VertexFormat::texture));

	// Vertex Normals
	/*glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat),
		(GLvoid*)offsetof(VertexFormat, VertexFormat::normals));*/

	glBindVertexArray(0);
	this->vao = VAO;
	this->vbos.push_back(VBO);
	this->vbos.push_back(EBO);

	this->model_matrix = glm::mat4(1.0);
	this->model_matrix = glm::rotate(this->model_matrix, 3.141f, glm::vec3(0.0f, 1.0f, 0.0f));
	//this->model_matrix = glm::scale(this->model_matrix,glm::vec3(0.3f, 0.3f, 0.3f));
}