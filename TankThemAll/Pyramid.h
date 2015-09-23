#pragma once
#include "Model.h"
#include "CubeIndex.h"

using namespace std;
namespace BasicEngine
{
	namespace Rendering
	{
		namespace Models
		{
			class Pyramid :
				public Model
			{
			public:
				Pyramid();
				~Pyramid();
				virtual void Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix) override;
				virtual void Update()           override;
				void Create();
				vector<CubeIndex*> listOfPyramid;
			};

		}
	}
}