#include "stdafx.h"
#include "Engine.h"
#include "CubeIndex.h"
#include "Diamond.h"

using namespace BasicEngine;

int main(int argc, char **argv)
{

	Engine* engine = new Engine();
	engine->Init();

	engine->GetShader_Manager()->CreateProgram("cubeShader",
		"Shaders\\Cube_Vertex_Shader.glsl",
		"Shaders\\Cube_Fragment_Shader.glsl");

	CubeIndex* cube = new CubeIndex();
	cube->SetProgram(engine->GetShader_Manager()->GetShader("cubeShader"));
	cube->Create();

	engine->GetModels_Manager()->SetModel("cube", cube);

	Diamond* diamond = new Diamond();
	diamond->SetProgram(engine->GetShader_Manager()->GetShader("cubeShader"));
	diamond->Create();

	engine->GetModels_Manager()->SetModel("diamond", diamond);

	engine->Run();

	delete engine;
	return 0;
}
