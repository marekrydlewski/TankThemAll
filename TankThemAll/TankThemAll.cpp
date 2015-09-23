#include "stdafx.h"
#include "Engine.h"
#include "Tank.h"
#include "Terrain.h"
#include "Tree1.h"
#include "Skybox.h"
#include "Diamond.h"
#include "Bullets.h"
#include <SOIL.h>
using namespace BasicEngine;
using namespace std;

int main(int argc, char **argv)
{
	//srand(time(0));
	Engine* engine = new Engine();
	engine->Init();

	engine->GetShader_Manager()->CreateProgram("baseShader",
		"Shaders\\Base_Vertex_Shader.glsl",
		"Shaders\\Base_Fragment_Shader.glsl");

	engine->GetShader_Manager()->CreateProgram("skyboxShader",
		"Shaders\\SkyboxVertexShader.glsl",
		"Shaders\\SkyboxFragmentShader.glsl");

	engine->GetShader_Manager()->CreateProgram("importedModelShader",
		"Shaders\\ImportedVertexShader.glsl",
		"Shaders\\ImportedFragmentShader.glsl");

	engine->GetShader_Manager()->CreateProgram("terrainShader",
		"Shaders\\TerrainVertexShader.glsl",
		"Shaders\\TerrainFragmentShader.glsl");

	Skybox* skybox = new Skybox();
	skybox->SetProgram(engine->GetShader_Manager()->GetShader("skyboxShader"));
	skybox->Create(engine->GetScene_Manager());

	engine->GetModels_Manager()->SetModel("skybox", skybox);

	Terrain* terrain = new Terrain();
	terrain->SetProgram(engine->GetShader_Manager()->GetShader("terrainShader"));
	terrain->Create("maps\\map.bmp");

	engine->GetModels_Manager()->SetModel("map", terrain);

	for (int i = 0; i < 20; i++)
	{
		Tree1* tree = new Tree1();
		tree->SetProgram(engine->GetShader_Manager()->GetShader("importedModelShader"));
		int signX = rand() % 2 ? 1 : -1;
		int signZ = rand() % 2 ? 1 : -1;
		tree->Create("models\\Tree1\\tree.obj", ((((float)rand()) / (float)RAND_MAX) * (signX * 50 - signX * 3)) + signX * 3, ((((float)rand()) / (float)RAND_MAX) * (signZ * 50 - signZ * 3)) + signZ * 3);

		std::string tmp = "";
		sprintf((char*)tmp.c_str(), "tree_%d", i);
		engine->GetModels_Manager()->SetModel(tmp, tree);
	}

	Tank* tank = new Tank();
	tank->SetProgram(engine->GetShader_Manager()->GetShader("importedModelShader"));
	tank->Create("models\\Tiger\\Tiger_I.obj");

	Diamond* diamond = new Diamond();
	diamond->SetProgram(engine->GetShader_Manager()->GetShader("baseShader"));
	diamond->Create();

	Bullets* bullets = new Bullets();
	bullets->SetProgram(engine->GetShader_Manager()->GetShader("baseShader"));
	bullets->Create();

	engine->GetModels_Manager()->SetModel("bullets", bullets);


	engine->GetModels_Manager()->SetModel("tank", tank);

	engine->GetScene_Manager()->BindTank("tank");
	engine->GetScene_Manager()->BindBullets("bullets");

	engine->Run();

	delete engine;
	return 0;
}
