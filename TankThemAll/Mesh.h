#pragma once

#include <vector>
#include "stdafx.h"
#include "VertexFormat.h"
#include "TextureWrap.h"
#include "Model.h"

using namespace BasicEngine::Rendering;
using namespace BasicEngine::Rendering::Models;


class Mesh : 
	public Model
{
	public:
		/*  Mesh Data  */
		std::vector<VertexFormat> vertices;
		std::vector<GLuint> indices;
		std::vector<TextureWrap> textures;
		/*  Functions  */
		Mesh(std::vector<VertexFormat> vertices, std::vector<GLuint> indices, std::vector<TextureWrap> textures);
		void Create(std::vector<VertexFormat> vertices, std::vector<GLuint> indices, std::vector<TextureWrap> textures);
		virtual void Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix) override final;
		virtual void Update() override final;
	private:
		/*  Functions    */
		void setupMesh();
};
