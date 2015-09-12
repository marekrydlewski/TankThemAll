#pragma once
#include "IGameObject.h"
namespace BasicEngine
{
	namespace Rendering
	{
		namespace Models
		{
			class Terrain :
				public IGameObject
			{
			public:
				Terrain();
				virtual ~Terrain();
				void Create(char *filename);

			private:
				void ComputeNormals();
				int width, height, channels;
				float *heights;
				float *normals;
			};
		}
	}
}
