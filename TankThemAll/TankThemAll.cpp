#include "stdafx.h"
#include "Engine.h"
#include "Diamond.h"
#include "ImportedModel.h"

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

	ImportedModel* tank = new ImportedModel();
	tank->SetProgram(engine->GetShader_Manager()->GetShader("cubeShader"));
	tank->Create("C:\\Projekty\\TankThemAll\\models\\Tiger\\Tiger_I.obj");

	engine->GetModels_Manager()->SetModel("tank", tank);

	engine->Run();

	delete engine;
	return 0;
}
