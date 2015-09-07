#pragma once
#include <iostream>
namespace BasicEngine
{
	namespace Core
	{
		namespace Init
		{
			class Init_GLEW
			{
			public:
				Init_GLEW();
				~Init_GLEW();

				static void Init();
			};
		}
	}
}