#pragma once
#include "VertexFormat.h"
#include <vector>
#include <map>

struct Model
{
	unsigned int vao;
	std::vector<unsigned int> vbos;

	Model(){}
};

class GameModels
{
public:
	GameModels();
	~GameModels();
	void CreateTriangleModel(const std::string& gameModelName);
	void DeleteModel(const std::string& gameModelName);
	GLuint GetModel(const std::string& gameModelName);
private:
	std::map<std::string, Model> GameModelList;//keep our models
};