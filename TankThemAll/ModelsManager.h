#pragma once
#include <map>
#include "IGameObject.h"
#include "Triangle.h"
#include "Quad.h"
#include "ShaderManager.h"

class ModelsManager
{
public:
	ModelsManager();
	~ModelsManager();

	void Draw();
	void Update();
	void DeleteModel(const std::string& gameModelName);
	const IGameObject& GetModel(const std::string& gameModelName) const;

private:
	std::map<std::string, IGameObject*> gameModelList;
};