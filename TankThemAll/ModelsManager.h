#pragma once
#include <unordered_map>
#include "ShaderManager.h"
#include "IGameObject.h"
#include "Triangle.h"
#include "Quad.h"

namespace BasicEngine
{
	using namespace Rendering;
	namespace Managers
	{
		class Models_Manager
		{
		public:
			Models_Manager();
			~Models_Manager();

			void Draw();
			void Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix);
			void Update();

			void DeleteModel(const std::string& gameModelName);
			IGameObject& GetModel(const std::string& gameModelName) const;
			IGameObject* GetModelPointer(const std::string& gameModelName) const;
			void DeleteModel_NDC(const std::string& gameModelName);
			IGameObject& GetModel_NDC(const std::string& gameModelName) const;

			void SetModel(const std::string& gameObjectName, IGameObject* gameObject);

			std::map<std::string, IGameObject*> gameModelList;
			std::map<std::string, IGameObject*> gameModelList_NDC;
		};
	}
}
