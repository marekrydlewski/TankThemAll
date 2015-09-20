#pragma once
#include "ImportedModel.h"

namespace BasicEngine
{
	namespace Rendering
	{
		namespace Models
		{

			class Tank :
				public ImportedModel
			{
			public:
				Tank();
				virtual ~Tank();
				glm::mat4 GetTankMatrix();
				void Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix);
				void TranslateMeshes();
				glm::mat4 tank_model_matrix; // it can be private later
				glm::vec3 tank_model_position; // it can be private later
				GLfloat tank_model_rotation;
			};


		}
	}
}