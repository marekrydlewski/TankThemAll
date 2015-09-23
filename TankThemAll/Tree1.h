#pragma once
#include "ImportedModel.h"
namespace BasicEngine
{
	namespace Rendering
	{
		namespace Models
		{
			class Tree1 :
				public ImportedModel
			{
			public:
				Tree1();
				virtual ~Tree1();
				void Create(GLchar *path, GLfloat offsetX, GLfloat offsetZ);
				void CheckCollision(glm::vec3 position, GLfloat radius);
				void Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix);
			private:
				bool isDrawn;
			};
		}
	}
}


