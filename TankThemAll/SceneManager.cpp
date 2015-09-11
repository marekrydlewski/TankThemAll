#include "stdafx.h"
#include "SceneManager.h"
using namespace BasicEngine;
using namespace Managers;
using namespace std;

bool keys[1024] = { false };
std::string x1 = "marek";

void CameraCallbackDown(int key, int x, int y){

	if (key >= 0 && key < 1024)
	{
		keys[key] = true;
	}
	cout << "down" << endl;
}

void CameraCallbackUp(int key, int x, int y){

	if (key >= 0 && key < 1024)
	{
		keys[key] = false;
	}
	cout << GLUT_KEY_LEFT << endl;
}


	
Scene_Manager::Scene_Manager()
{

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	/*view_matrix = glm::lookAt(
		glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		);
		*/

	camera = new Camera(glm::vec3(1, 1, 10), glm::vec3(0, 1, 0), YAW, PITCH);
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
	glutSpecialFunc(&CameraCallbackDown);
	glutSpecialUpFunc(CameraCallbackUp);
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

void Scene_Manager::KeyboardHandler(unsigned char key, int x, int y)
{


}

void Scene_Manager::KeyboardSpecialHandler(int key, int x, int y)
{


}