#pragma once
#include<vector>
#include "Mesh.h"
#include "Model.h"

using namespace BasicEngine::Rendering::Models;

class ImportedModel : public Model
{
public:
	/*  Functions   */
	ImportedModel();
	virtual ~ImportedModel();
	void Create(GLchar* path);
	virtual void Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix) override final;
	virtual void Update() override final;
	std::vector<Mesh> getMeshes();
private:
	/*  Model Data  */
	std::vector<Mesh> meshes;
	std::string directory;
	std::vector<TextureWrap> textures_loaded;
	/*  Functions   */
	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<TextureWrap> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
		std::string typeName);
	aiString excludeFilename(aiString name);
	std::string excludePath(std::string name);
};

