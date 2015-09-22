#pragma once
#include "IListener.h"
#include "ModelsManager.h"
#include "Camera.h"
#include "TankCamera.h"
#include "Tank.h"

namespace BasicEngine
{
	namespace Managers
	{
		class Scene_Manager : public Core::IListener
		{
		public:
			Scene_Manager();
			~Scene_Manager();

			virtual void NotifyBeginFrame();
			virtual void NotifyDisplayFrame();
			virtual void NotifyEndFrame();
			virtual void NotifyReshape(int width, int height, int previos_width, int previous_height);
			virtual void MakeCameraMove(GLfloat);
			virtual void ProcessMouseMove();
			virtual glm::mat4 GetViewFromCamera();

			void BindTank(std::string);
			void SetCameraOffset(glm::vec3 x){
				camera->SetTankOffset(x);
			}
			void SetModelsManager(Managers::Models_Manager* models_manager);
			glm::vec3 GetTankCameraPosition(bool);
	
				
		private:
			Managers::Models_Manager* models_manager;
			Rendering::TankCamera* camera;
			Rendering::Camera* cameraView;
			Rendering::Models::Tank* tank;
			glm::mat4 projection_matrix;
			glm::mat4 view_matrix;
			void EnableCallbacks();
			void MakeMouseMove(int x, int y);
		};

	}
}