
#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "BMPHeaders.h"

namespace BasicEngine
{
	namespace Rendering
	{
		class TextureLoader
		{
			public:
				static GLuint loadDDS(const char * imagepath);
				static unsigned int LoadTexture(const std::string& filename, int &width, int &height);

			private:

				static void LoadBMPFile(const std::string& filename, unsigned int& width, unsigned int& height, unsigned char*& data);
		};



	}
}