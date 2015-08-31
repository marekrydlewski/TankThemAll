#include "stdafx.h"
#include "ModelsManager.h"


ModelsManager::ModelsManager()
{
	Cube* cube = new Cube();
	cube->SetProgram(ShaderManager::GetShader("cubeShader"));
	cube->Create();
	gameModelList["cube"] = cube;

	Triangle* triangle = new Triangle();
	triangle->SetProgram(ShaderManager::GetShader("colorPrimitiveShader"));
	triangle->Create();
	gameModelList["triangle"] = triangle;

}

ModelsManager::~ModelsManager()
{
	//auto -it's a map iterator
	for (auto& model : gameModelList)
	{
		delete model.second;
	}
	gameModelList.clear();
}

void ModelsManager::DeleteModel(const std::string& gameModelName)
{
	IGameObject* model = gameModelList[gameModelName];
	model->Destroy();
	gameModelList.erase(gameModelName);
}

const IGameObject& ModelsManager::GetModel(const std::string& gameModelName) const
{
	return (*gameModelList.at(gameModelName));
}

void ModelsManager::Update()
{
	//auto -it's a map iterator
	for (auto& model : gameModelList)
	{
		model.second->Update();
	}
}

void ModelsManager::Draw()
{
	//auto -it's a map iterator
	for (auto& model : gameModelList)
	{
		model.second->Draw();
	}
}

void ModelsManager::Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix)
{
	for (auto model : gameModelList)
	{
		model.second->Draw(projection_matrix, view_matrix);
	}
}