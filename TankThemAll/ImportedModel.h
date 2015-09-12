#pragma once
#include<vector>
#include "Mesh.h"
#include "Model.h"

using namespace BasicEngine::Rendering::Models;

class ImportedModel : public IGameObject
{
public:
	/*  Functions   */
	ImportedModel();
	virtual ~ImportedModel();

	void Create(GLchar* path);
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
	/*  Model Data  */
	std::vector<Mesh*> meshes;
	std::string directory;
	std::vector<TextureWrap> textures_loaded;
	GLuint program;
	/*  Functions   */
	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh* processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<TextureWrap> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
		std::string typeName);
	aiString excludeFilename(aiString name);
	aiString excludePath(std::string name);
};

