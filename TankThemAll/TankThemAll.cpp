#include "stdafx.h"
#include "Engine.h"
#include "Tank.h"
#include "Diamond.h"

using namespace BasicEngine;

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
	
	
	Tank* tank = new Tank();
	tank->SetProgram(engine->GetShader_Manager()->GetShader("importedModelShader"));
	tank->Create("models\\Tiger\\Tiger_I.obj");

	Diamond* diamond = new Diamond();
	diamond->SetProgram(engine->GetShader_Manager()->GetShader("baseShader"));
	diamond->Create();
	engine->GetModels_Manager()->SetModel("tank", tank);
	engine->GetModels_Manager()->SetModel("diamond", diamond);

	engine->BindTank("tank");
	engine->Run();

	delete engine;
	return 0;
}
