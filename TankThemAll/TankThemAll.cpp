#include "stdafx.h"
#include "Engine.h"
#include "Tank.h"
#include "Terrain.h"
#include "Tree1.h"
#include "Diamond.h"
#include "Bullet.h"
#include <SOIL.h>
using namespace BasicEngine;
using namespace std;

int main(int argc, char **argv)
{

	Engine* engine = new Engine();
	engine->Init();

	engine->GetShader_Manager()->CreateProgram("baseShader",
		"Shaders\\Base_Vertex_Shader.glsl",
		"Shaders\\Base_Fragment_Shader.glsl");


	engine->GetShader_Manager()->CreateProgram("importedModelShader",
		"Shaders\\ImportedVertexShader.glsl",
		"Shaders\\ImportedFragmentShader.glsl");

	engine->GetShader_Manager()->CreateProgram("terrainShader",
		"Shaders\\TerrainVertexShader.glsl",
		"Shaders\\TerrainFragmentShader.glsl");

	Terrain* terrain = new Terrain();
	terrain->SetProgram(engine->GetShader_Manager()->GetShader("terrainShader"));
	terrain->Create("maps\\map.bmp");

	engine->GetModels_Manager()->SetModel("map", terrain);

	for (int i = 0; i < 10; i++)
	{
		Tree1* tree = new Tree1();
		tree->SetProgram(engine->GetShader_Manager()->GetShader("importedModelShader"));
		tree->Create("models\\Tree1\\tree.obj", ((((float)rand()) / (float)RAND_MAX) * (20 - (-20))) + (-20), ((((float)rand()) / (float)RAND_MAX) * (20 - (-20))) + (-20));

		std::string tmp="";
		sprintf((char*)tmp.c_str(), "tree_%d", i);
		engine->GetModels_Manager()->SetModel(tmp, tree);
	}

	Tank* tank = new Tank();
	tank->SetProgram(engine->GetShader_Manager()->GetShader("importedModelShader"));
	tank->Create("models\\Tiger\\Tiger_I.obj");

	Diamond* diamond = new Diamond();
	diamond->SetProgram(engine->GetShader_Manager()->GetShader("baseShader"));
	diamond->Create();

	Bullet* bullet = new Bullet();
	bullet->SetProgram(engine->GetShader_Manager()->GetShader("baseShader"));
	bullet->Create();

	engine->GetModels_Manager()->SetModel("bullet", bullet);


	engine->GetModels_Manager()->SetModel("tank", tank);

	engine->GetScene_Manager()->BindTank("tank");
	engine->GetScene_Manager()->BindBullet("bullet");

	engine->Run();

	delete engine;
	return 0;
}
