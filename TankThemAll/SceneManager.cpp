#include "stdafx.h"
#include "SceneManager.h"
using namespace BasicEngine;
using namespace Managers;

bool keys[1024] = { false };
int x = 7;

void gunwo(){
	x = 2;
}


Scene_Manager::Scene_Manager()
{

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	gunwo();
	/*view_matrix = glm::lookAt(
		glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		);
		*/

	camera = new Camera(glm::vec3(1, 1, 10), glm::vec3(0, 1, 0), YAW, PITCH);
	projection_matrix = glm::perspective(45.0f, 16.0f / 9.0f, 0.1f, 100.0f);


}

Scene_Manager::~Scene_Manager()
{
	delete camera;
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

	x += 2;

}

void Scene_Manager::SetModelsManager(Managers::Models_Manager* models_m)
{
	models_manager = models_m;
}

glm::mat4 Scene_Manager::GetViewFromCamera()
{
	return this->camera->GetViewMatrix();
}

void Scene_Manager::MakeCameraMove()
{
	std::cout << x;
}

void Scene_Manager::KeyboardHandler(unsigned char key, int x, int y)
{


}

void Scene_Manager::KeyboardSpecialHandler(int key, int x, int y)
{


}