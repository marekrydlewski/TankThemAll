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
			class Bullet : 
				public Model
			{
			public:
				Bullet();
				~Bullet();

				bool isFired;
				virtual void Create();
				virtual void Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix) override final;
				virtual void Spawn(const glm::mat4& bullet_model_matrix, GLfloat angle);	
				virtual void Update() override final;

			private:
				GLfloat rotate;
				GLfloat angle;
				void calculateNormals(std::vector<GLuint> indices, std::vector<VertexFormat> &vertices);

			};
		}
	}
}