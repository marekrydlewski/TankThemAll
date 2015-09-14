#pragma once

#include "Camera.h"
#include <vector>
#include <iostream>

namespace BasicEngine{
	namespace Rendering{

		class TankCamera :
			public BasicEngine::Rendering::Camera
		{
		public:
			void SetTankOffset(glm::vec3);
			TankCamera();
			virtual ~TankCamera();
		};
	}
}