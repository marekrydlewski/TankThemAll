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
			private:
				glm::mat4 tank_model_matrix;
			};


		}
	}
}