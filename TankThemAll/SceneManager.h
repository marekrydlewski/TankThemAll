#pragma once
#include "IListener.h"
#include "ModelsManager.h"
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

			void SetModelsManager(Managers::Models_Manager* models_manager);

		private:
			Managers::Models_Manager* models_manager;

			glm::mat4 projection_matrix;
			glm::mat4 view_matrix;
		};

	}
}