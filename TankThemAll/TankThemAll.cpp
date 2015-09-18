#include "stdafx.h"
#include "Engine.h"
#include "Tank.h"
#include "Terrain.h"

using namespace BasicEngine;

int main(int argc, char **argv)
{

	Engine* engine = new Engine();
	engine->Init();
	
	engine->GetShader_Manager()->CreateProgram("cubeShader",
		"Shaders\\Cube_Vertex_Shader.glsl",
		"Shaders\\Cube_Fragment_Shader.glsl");
	

	
	engine->GetShader_Manager()->CreateProgram("importedModelShader",
		"Shaders\\ImportedVertexShader.glsl",
		"Shaders\\ImportedFragmentShader.glsl");

	Terrain* terrain = new Terrain();
	terrain->SetProgram(engine->GetShader_Manager()->GetShader("cubeShader"));
	terrain->Create("maps\\map.bmp");

	engine->GetModels_Manager()->SetModel("map", terrain);
	
	Tank* tank = new Tank();
	tank->SetProgram(engine->GetShader_Manager()->GetShader("importedModelShader"));
	tank->Create("models\\Tiger\\Tiger_I.obj");

	engine->GetModels_Manager()->SetModel("tank", tank);
	
	engine->Run();

	delete engine;
	return 0;
}
