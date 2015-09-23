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
bool specialMode = false;
bool enableEntrySpecialMode = true;
bool shoot = false;
GLfloat scroll = 45.0f;
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

void CameraCallbackDownChar(unsigned char key, int x, int y)
{

	if (key >= 0 && key < 1024)
	{
		keys[key] = true;
	}
}

void CameraCallbackUpChar(unsigned char key, int x, int y)
{

	if (key >= 0 && key < 1024)
	{
		keys[key] = false;
	}
	if (key == 'x')
	{
		specialMode = !specialMode;
		if (specialMode)
			enableEntrySpecialMode = true;
		scroll = 45.0f;
	}
	else if ((int)key == 32)//space
	{
		shoot = true;
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
		activeUpdateCamera = true;
	}
}

void ScrollCallback(int button, int state, int x, int y)
{
	if (button == 3)
	{
		scroll += 0.01f;
		if (scroll > 47.0)
			scroll = 47.0;
	}
	else if (button == 4)
	{
		scroll -= 0.01f;
		if (scroll < 44.0f)
			scroll = 44.0f;
	}
}


/* ... */

Scene_Manager::Scene_Manager()
{
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE); //add to enable culling
	//camera = new TankCamera(glm::vec3(1, 1, 10), glm::vec3(0, 1, 0), YAW, PITCH);
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
	//glutSpecialFunc(CameraCallbackDown);
	//glutSpecialUpFunc(CameraCallbackUp);
	glutKeyboardFunc(CameraCallbackDownChar);
	glutKeyboardUpFunc(CameraCallbackUpChar);
	glutMouseFunc(ScrollCallback);
	glutPassiveMotionFunc(CameraMouseCallback);
}

void Scene_Manager::NotifyBeginFrame()
{
	models_manager->Update();
	CheckBulletsCollision();
}

void Scene_Manager::NotifyDisplayFrame()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	glEnable(GL_BLEND);											// added for multitexturing tutorial
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//tank->tank_model_matrix -= glm::translate(tank->tank_model_matrix, camera->GetTranslation()); //diffrence between old state end new state
	//tank->tank_model_position -= camera->GetTranslation();
	models_manager->Draw();
	models_manager->Draw(projection_matrix, view_matrix);
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
	auto temp = this->camera->Position;
	if (keys[char('w')])
	{
		if (specialMode)
			cameraView->ProcessKeyboard(FORWARD, deltaTime);
		else
			camera->ProcessKeyboard(FORWARD, deltaTime);
	}

	if (keys[char('s')])
	{
		if (specialMode)
			cameraView->ProcessKeyboard(BACKWARD, deltaTime);
		else
			camera->ProcessKeyboard(BACKWARD, deltaTime);
	}
	if (keys[char('a')])
	{
		if (specialMode)
			cameraView->ProcessKeyboard(LEFT, deltaTime);
		else
			camera->ProcessKeyboard(LEFT, deltaTime);
	}
	if (keys[char('d')])
	{
		if (specialMode)
			cameraView->ProcessKeyboard(RIGHT, deltaTime);
		else
			camera->ProcessKeyboard(RIGHT, deltaTime);
	}
	if (keys[char('q')])
	{
		if (!specialMode)
			camera->ProcessKeyboard(LEFT_TURRET, deltaTime);
	}
	if (keys[char('e')])
	{
		if (!specialMode)
			camera->ProcessKeyboard(RIGHT_TURRET, deltaTime);
	}
	if (keys[27])//ESC escape
	{
		glutLeaveMainLoop();
	}

	//calulate tank parameters
	this->tank->tank_model_position += glm::rotateY(this->camera->Position - temp, this->camera->Yaw + 90.0f);
	this->tank->tank_model_rotation = this->camera->Yaw + 90.0f;
	this->tank->tank_model_turret_rotation = this->camera->TurretYaw;

	//check trees for collision
	glm::mat4 check_pos = glm::mat4(1.0f);
	check_pos = glm::translate(check_pos, this->tank->tank_model_position);
	check_pos = glm::translate(check_pos, glm::rotateY(glm::vec3(3.35, 0.0f, 0.0f), this->tank->tank_model_rotation + glm::radians(90.0f)));

	glm::mat4 check_pos2 = glm::mat4(1.0f);
	check_pos2 = glm::translate(check_pos, this->tank->tank_model_position);
	check_pos2 = glm::translate(check_pos, glm::rotateY(glm::vec3(2.65, 0.0f, 0.0f), this->tank->tank_model_rotation + glm::radians(270.0f)));
	this->CheckTrees(glm::vec3(check_pos[3][0], check_pos[3][1], check_pos[3][2]), 2.7f);
	this->CheckTrees(glm::vec3(check_pos2[3][0], check_pos2[3][1], check_pos2[3][2]), 2.7f);

	

	if (shoot) //shoot
	{
		shoot = false;
		glm::mat4 bullet_pos = glm::mat4(1.0f);
		bullet_pos = glm::translate(bullet_pos, this->tank->tank_model_position);
		auto bullet_angle = this->tank->tank_model_rotation +
			this->tank->tank_model_turret_rotation
			+ glm::radians(90.0f);
		bullet_pos = glm::translate(bullet_pos, glm::rotateY(glm::vec3(6.35, 2.2f, 0.0f), bullet_angle)); //compute start bullet possition
		//bullet_pos = glm::translate(bullet_pos, glm::rotateY() );

		bullet_pos = glm::scale(bullet_pos, glm::vec3(0.3f, 0.3f, 0.3f));
		this->bullets->AddBullet(bullet_pos, bullet_angle);

		//this->bullets->AddBullet(check_pos, 0.0f);

	}


	if (!specialMode) //normal mode
		this->view_matrix = glm::lookAt(this->tank->tank_model_position + glm::rotateY(this->camera->offset, this->tank->tank_model_rotation + this->tank->tank_model_turret_rotation), this->tank->tank_model_position, glm::vec3(0, 1.0f, 0.0f));
	else
	{ //free camera
		if (enableEntrySpecialMode)
		{
			cameraView->Position = this->cameraView->Position = (this->tank->tank_model_position + glm::vec3(0.0f, 5.0f, 0.0f));
			enableEntrySpecialMode = false;
		}
		this->view_matrix = this->cameraView->GetViewMatrix();
	}
	projection_matrix = glm::perspective(scroll, 16.0f / 9.0f, 0.1f, 100.0f);
}

void Scene_Manager::MakeMouseMove(int x, int y)
{
	if (activeUpdateCamera){
		this->cameraView->ProcessMouseMovement(x, y); //add false to disable constraint pitch
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
		std::cout << "ENGINE: BindTank function Error: Cannot find tank object" << std::endl;
	else
		std::cout << "ENGINE: Camera successfully found tank object" << std::endl;

	this->tank->tank_model_position = glm::vec3(10.0f, 0.0f, 0.0f);
	camera = new TankCamera(this->tank->tank_model_position, glm::vec3(0, 1, 0), YAW, PITCH);
	camera->SetTankOffset(glm::vec3(0, 5, 15));
	cameraView = new Camera(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), YAW, PITCH);

}

glm::vec3 Scene_Manager::GetTankCameraPosition(bool special = false)
{
	if (!special)
		return this->tank->tank_model_position + glm::rotateY(this->camera->offset, this->tank->tank_model_rotation + this->tank->tank_model_turret_rotation);
	else
		return this->tank->tank_model_position + glm::vec3(0.0f, 5.0f, 0.0f);
}

void Scene_Manager::BindBullets(std::string name)
{

	bullets = dynamic_cast<Bullets*>(models_manager->GetModelPointer(name));
	if (bullets == nullptr)
		std::cout << "ENGINE: BindBullet function Error: Cannot find bullets object" << std::endl;
	else
		std::cout << "ENGINE: Camera successfully found bullets object" << std::endl;


}

void Scene_Manager::CheckTrees(glm::vec3 position, GLfloat radius)
{
	Tree1* tree = nullptr;
	for (auto model : models_manager->gameModelList)
	{
		auto name = model.first.substr(0, 5);
		if (name == "tree_")
		{
			tree = dynamic_cast<Tree1*>(model.second);
			if (tree != nullptr)
			{
				tree->CheckCollision(position, radius);
			}
		}

	}
}


void Scene_Manager::CheckBulletsCollision()
{
	for (auto& bullet : this->bullets->listOfBullets)
	{
		this->CheckTrees(bullet->GetPosition(), 0.7f);
	}
}