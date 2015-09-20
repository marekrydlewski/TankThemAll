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
			glm::vec3 GetTranslation();
			TankCamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH):
				Camera(position, up, yaw, pitch){}
			TankCamera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch) :
				Camera(posX, posY, posZ, upX, upY, upZ, yaw, pitch){};
			void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime);
			GLfloat AngleY();
			glm::mat4 GetViewMatrix()
			{
				return glm::lookAt(this->Position, this->Position + this->Front, this->Up);
			}
			virtual ~TankCamera();
			glm::vec3 offset;
		};
	}
}