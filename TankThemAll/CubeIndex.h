#pragma once

#include "Model.h"
#include <time.h>
#include <stdarg.h>

namespace BasicEngine
{
	namespace Rendering
	{
		namespace Models
		{
			class CubeIndex : public Model
			{
			public:
				CubeIndex();
				~CubeIndex();

				void Create(GLfloat offsetX, GLfloat offsetY, GLfloat offsetZ);
				virtual void Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix) override final;
				virtual void Update() override final;
				bool CheckCollision(glm::vec3 collider_position, GLfloat radius);
				void ActivateFall();

			private:
				GLfloat rotate;
				bool isDrawn;
				void calculateNormals(std::vector<GLuint> indices, std::vector<VertexFormat> &vertices);
			};
		}
	}
}

