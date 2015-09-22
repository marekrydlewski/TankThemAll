#pragma once
#include "IGameObject.h"

namespace BasicEngine
{
	namespace Rendering
	{
		namespace Models
		{
			class Bullets :
				public IGameObject
			{
			public:
				Bullets();
				virtual ~Bullets();
			};
		}

	}
}