#pragma once

#include <vector>
#include "stdafx.h"
#include "VertexFormat.h"
#include "TextureWrap.h"

using namespace BasicEngine::Rendering;


class Mesh {
	public:
		/*  Mesh Data  */
		std::vector<VertexFormat> vertices;
		std::vector<GLuint> indices;
		std::vector<TextureWrap> textures;
		/*  Functions  */
		Mesh(std::vector<BasicEngine::Rendering::VertexFormat> vertices, std::vector<GLuint> indices, std::vector<TextureWrap> textures);
		void Draw();
		void SetProgram(GLuint program);
	private:
		/*  Render data  */
		GLuint VAO, VBO, EBO;
		GLuint program;
		/*  Functions    */
		void setupMesh();
};
