#pragma once
#include "IGameObject.h"
#include "SceneManager.h"
namespace BasicEngine
{
	namespace Rendering
	{
		namespace Models
		{
			class Skybox :
				public IGameObject
			{
			public:
				Skybox();
				virtual ~Skybox();
				void Create(BasicEngine::Managers::Scene_Manager *sceneManager);
				virtual void Draw() override;
				virtual void Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix) override;
				virtual void Update() override;
				virtual void Destroy() override;
				virtual void SetProgram(GLuint program) override;

				virtual GLuint GetVao()                     const override;
				virtual const std::vector<GLuint> GetVbos() const override;

				virtual const GLuint GetTexture(std::string textureName) const override;
				virtual void SetTexture(std::string textureName, GLuint texture) override;

				GLuint loadCubemap(vector<const GLchar*> faces);
			private:
				BasicEngine::Managers::Scene_Manager *_sceneManager;
				GLuint vao;
				std::vector<GLuint> vbos;
				glm::mat4 model_matrix;
				GLuint program;
				std::map<std::string, GLuint> textures;
				std::vector<const GLchar*> faces;
			};
		}
	}
}