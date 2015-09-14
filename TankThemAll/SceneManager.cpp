#include "stdafx.h"
#include "SceneManager.h"
using namespace BasicEngine;
using namespace Managers;
using namespace Models;
using namespace std;

/* ... */
bool keys[1024] = { false };
bool activeUpdateCamera = false;
bool firstMouse = true;
GLfloat xoffset, yoffset;
GLfloat lastX, lastY;


void CameraCallbackDown(int key, int x, int y)
{

	if (key >= 0 && key < 1024)
	{
		keys[key] = true;
	}
}

void CameraCallbackUp(int key, int x, int y)
{

	if (key >= 0 && key < 1024)
	{
		keys[key] = false;
	}
}

void CameraMouseCallback(int xpos, int ypos)
{
	if (activeUpdateCamera == false){
		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}
		xoffset = xpos - lastX;
		yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left
		lastX = xpos;
		lastY = ypos;
		// Update Front, Right and Up Vectors using the updated Eular angles
		activeUpdateCamera = true;
	}
}


/* ... */

Scene_Manager::Scene_Manager()
{
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE); //add to enable culling

	camera = new TankCamera(glm::vec3(1, 1, 10), glm::vec3(0, 1, 0), YAW, PITCH);
	projection_matrix = glm::perspective(45.0f, 16.0f / 9.0f, 0.1f, 100.0f);

	//enable callbacks
	this->EnableCallbacks();

}


Scene_Manager::~Scene_Manager()
{
	delete camera;
}

void Scene_Manager::EnableCallbacks()
{
	glutSpecialFunc(CameraCallbackDown);
	glutSpecialUpFunc(CameraCallbackUp);
	glutPassiveMotionFunc(CameraMouseCallback);
}

void Scene_Manager::NotifyBeginFrame()
{
	models_manager->Update();
}

void Scene_Manager::NotifyDisplayFrame()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	glEnable(GL_BLEND);											// added for multitexturing tutorial
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	models_manager->Draw();
	models_manager->Draw(projection_matrix, GetViewFromCamera());
}

void Scene_Manager::NotifyEndFrame()
{
}

void Scene_Manager::NotifyReshape(int width, int height,
	int previos_width, int previous_height)
{

}

void Scene_Manager::SetModelsManager(Managers::Models_Manager* models_m)
{
	models_manager = models_m;
}

glm::mat4 Scene_Manager::GetViewFromCamera()
{
	return this->camera->GetViewMatrix();
}

void Scene_Manager::MakeCameraMove(GLfloat deltaTime)
{
	if (keys[GLUT_KEY_UP])
		camera->ProcessKeyboard(FORWARD, deltaTime);
	if (keys[GLUT_KEY_DOWN])
		camera->ProcessKeyboard(BACKWARD, deltaTime);
	if (keys[GLUT_KEY_LEFT])
		camera->ProcessKeyboard(LEFT, deltaTime);
	if (keys[GLUT_KEY_RIGHT])
		camera->ProcessKeyboard(RIGHT, deltaTime);
}

void Scene_Manager::MakeMouseMove(int x, int y)
{
	if (activeUpdateCamera){
		this->camera->ProcessMouseMovement(x, y); //add false to disable constraint pitch
		activeUpdateCamera = false;
	}
}

void Scene_Manager::ProcessMouseMove()
{
	MakeMouseMove(xoffset, yoffset);
}


void Scene_Manager::BindTank(std::string name)
{

	tank = dynamic_cast<Tank*>(models_manager->GetModelPointer(name));
	if (tank == nullptr)
		std::cout << "BindTank function Error: Cannot find tank object" << std::endl;

}