#pragma once
#include "IGameObject.h"
namespace BasicEngine
{
	namespace Rendering
	{
		namespace Models
		{
			class Terrain :
				public IGameObject
			{
			public:
				Terrain();
				virtual ~Terrain();
				void Create(char *filename);
				virtual void Draw() override;
				virtual void Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix) override;
				virtual void Update() override;
				virtual void Destroy() override;
				virtual void SetProgram(GLuint program) override;

				virtual GLuint GetVao()                     const override;
				virtual const std::vector<GLuint> GetVbos() const override;

				virtual const GLuint GetTexture(std::string textureName) const override;
				virtual void SetTexture(std::string textureName, GLuint texture) override;
			private:
				void ComputeNormals();
				int width, height, channels;
				int centerX, centerZ;
				float scaleMap;
				float** heights;
				glm::vec3** vertexNormals;
				std::vector<glm::vec3> faceNormals;
				GLuint program;
				GLuint vao;
				std::vector<GLuint> vbos;
				glm::mat4 model_matrix;
			};
		}
	}
}
