#include "stdafx.h"
#include "TankCamera.h"
using namespace std;
using namespace BasicEngine;
using  namespace Rendering;


TankCamera::~TankCamera()
{
}

void TankCamera::SetTankOffset(glm::vec3 offset)
{
	this->offset = offset;

}

void TankCamera::ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime)
{
	GLfloat velocity = this->MovementSpeed * deltaTime;
	if (direction == FORWARD)
		this->Position += this->Front * velocity;
	if (direction == BACKWARD)
		this->Position -= this->Front * velocity;
	if (direction == LEFT)
		this->Yaw += velocity*0.1;
	if (direction == RIGHT)
		this->Yaw += -velocity*0.1;
	if (direction == RIGHT_TURRET)
		this->TurretYaw += -velocity*0.1;
	if (direction == LEFT_TURRET)
		this->TurretYaw += velocity*0.1;
	this->updateCameraVectors();
}