#pragma once
#include "stdafx.h"
namespace BasicEngine
{
	namespace Rendering
	{
		struct TextureWrap {
			GLuint id;
			std::string type;
			aiString path;  // We store the path of the texture to compare with other textures
		};
	}
}
