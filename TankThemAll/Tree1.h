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
			};
		}
	}
}


