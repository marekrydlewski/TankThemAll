#include "stdafx.h"
#include "Engine.h"
#include "Tank.h"
#include "Terrain.h"
#include "Tree1.h"
#include "Skybox.h"
#include "Diamond.h"
#include "Bullets.h"
#include "CubeIndex.h"
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

	engine->GetShader_Manager()->CreateProgram("bulletShader",
		"Shaders\\BulletVertexShader.glsl",
		"Shaders\\BulletFragmentShader.glsl");

	Skybox* skybox = new Skybox();
	skybox->SetProgram(engine->GetShader_Manager()->GetShader("skyboxShader"));
	skybox->Create(engine->GetScene_Manager());

	engine->GetModels_Manager()->SetModel("skybox", skybox);

	Terrain* terrain = new Terrain();
	terrain->SetProgram(engine->GetShader_Manager()->GetShader("terrainShader"));
	terrain->Create("maps\\map.bmp");

	engine->GetModels_Manager()->SetModel("map", terrain);

	for (int i = 0; i < 50; i++)
	{
		Tree1* tree = new Tree1();
		tree->SetProgram(engine->GetShader_Manager()->GetShader("importedModelShader"));
		int signX = rand() % 2 ? 1 : -1;
		int signZ = rand() % 2 ? 1 : -1;
		tree->Create("models\\Tree1\\tree.obj", ((((float)rand()) / (float)RAND_MAX) * (signX * 65 - signX * 3)) + signX * 3, ((((float)rand()) / (float)RAND_MAX) * (signZ * 65 - signZ * 3)) + signZ * 3);

		std::string tmp = "";
		sprintf((char*)tmp.c_str(), "tree_%d", i);
		engine->GetModels_Manager()->SetModel(tmp, tree);
	}

	for (int i = 0; i < 8; i++)
	{
		int XorZ = rand() % 2;
		int signX = rand() % 2 ? 1 : -1;
		int signZ = rand() % 2 ? 1 : -1;
		GLfloat Xoffset = ((((float)rand()) / (float)RAND_MAX) * (signX * 60 - signX * 3)) + signX * 3;
		GLfloat Zoffset = ((((float)rand()) / (float)RAND_MAX) * (signZ * 60 - signZ * 3)) + signZ * 3;
		for (int j = 0; j < 4; j++)
		{
			CubeIndex* box = new CubeIndex();
			box->SetProgram(engine->GetShader_Manager()->GetShader("importedModelShader"));
			XorZ == 0 ? box->Create(Xoffset + j*2, 0, Zoffset) : box->Create(Xoffset, 0, Zoffset + j*2);

			std::string tmp = "";
			sprintf((char*)tmp.c_str(), "bunch_%d_#box_%d", i, j);
			engine->GetModels_Manager()->SetModel(tmp, box);
		}
		for (int j = 0; j < 3; j++)
		{
			CubeIndex* box = new CubeIndex();
			box->SetProgram(engine->GetShader_Manager()->GetShader("importedModelShader"));
			XorZ == 0 ? box->Create(Xoffset + 1 + j * 2, 2, Zoffset) : box->Create(Xoffset, 2, Zoffset + 1 + j * 2);

			std::string tmp = "";
			sprintf((char*)tmp.c_str(), "bunch_%d_#box_%d", i, j+4);
			engine->GetModels_Manager()->SetModel(tmp, box);
		}
		for (int j = 0; j < 2; j++)
		{
			CubeIndex* box = new CubeIndex();
			box->SetProgram(engine->GetShader_Manager()->GetShader("importedModelShader"));
			XorZ == 0 ? box->Create(Xoffset + 2 + j * 2, 4, Zoffset) : box->Create(Xoffset, 4, Zoffset + 2 + j * 2);

			std::string tmp = "";
			sprintf((char*)tmp.c_str(), "bunch_%d_#box_%d", i, j + 7);
			engine->GetModels_Manager()->SetModel(tmp, box);
		}
		CubeIndex* box = new CubeIndex();
		box->SetProgram(engine->GetShader_Manager()->GetShader("importedModelShader"));
		XorZ == 0 ? box->Create(Xoffset + 3, 6, Zoffset) : box->Create(Xoffset, 6, Zoffset + 3);

		std::string tmp = "";
		sprintf((char*)tmp.c_str(), "bunch_%d_#box_9", i);
		engine->GetModels_Manager()->SetModel(tmp, box);
	}


	Tank* tank = new Tank();
	tank->SetProgram(engine->GetShader_Manager()->GetShader("importedModelShader"));
	tank->Create("models\\Tiger\\Tiger_I.obj");

	Bullets* bullets = new Bullets();
	bullets->SetProgram(engine->GetShader_Manager()->GetShader("bulletShader"));
	bullets->Create();

	engine->GetModels_Manager()->SetModel("bullets", bullets);


	engine->GetModels_Manager()->SetModel("tank", tank);

	engine->GetScene_Manager()->BindTank("tank");
	engine->GetScene_Manager()->BindBullets("bullets");

	engine->Run();

	delete engine;
	return 0;
}
