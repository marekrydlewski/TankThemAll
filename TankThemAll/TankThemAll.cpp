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
	//tank->SetProgram(engine->GetShader_Manager()->GetShader("cubeShader"));
	tank->Create("C:\\Projekty\\TankThemAll\\models\\Tiger\\Tiger_I.obj");

	//engine->GetModels_Manager()->SetModel("tank", tank);

	std::vector<Mesh> sampleMeshes = tank->getMeshes();
	Mesh* cannon = new Mesh(sampleMeshes[0].vertices, sampleMeshes[0].indices, sampleMeshes[0].textures);
	cannon->SetProgram(engine->GetShader_Manager()->GetShader("cubeShader"));

	engine->GetModels_Manager()->SetModel("cannon", cannon);

	Mesh* turret = new Mesh(sampleMeshes[1].vertices, sampleMeshes[1].indices, sampleMeshes[1].textures);
	turret->SetProgram(engine->GetShader_Manager()->GetShader("cubeShader"));

	engine->GetModels_Manager()->SetModel("turret", turret);

	Mesh* hull = new Mesh(sampleMeshes[2].vertices, sampleMeshes[2].indices, sampleMeshes[2].textures);
	hull->SetProgram(engine->GetShader_Manager()->GetShader("cubeShader"));

	engine->GetModels_Manager()->SetModel("hull", hull);

	Mesh* wheel_1 = new Mesh(sampleMeshes[3].vertices, sampleMeshes[3].indices, sampleMeshes[3].textures);
	wheel_1->SetProgram(engine->GetShader_Manager()->GetShader("cubeShader"));

	engine->GetModels_Manager()->SetModel("wheel_1", wheel_1);

	Mesh* wheel_2 = new Mesh(sampleMeshes[4].vertices, sampleMeshes[4].indices, sampleMeshes[4].textures);
	wheel_2->SetProgram(engine->GetShader_Manager()->GetShader("cubeShader"));

	Mesh* track_1 = new Mesh(sampleMeshes[5].vertices, sampleMeshes[5].indices, sampleMeshes[5].textures);
	track_1->SetProgram(engine->GetShader_Manager()->GetShader("cubeShader"));

	engine->GetModels_Manager()->SetModel("track_1", track_1);

	Mesh* track_2 = new Mesh(sampleMeshes[6].vertices, sampleMeshes[6].indices, sampleMeshes[6].textures);
	track_2->SetProgram(engine->GetShader_Manager()->GetShader("cubeShader"));

	engine->GetModels_Manager()->SetModel("track_2", track_2);

	engine->GetModels_Manager()->SetModel("wheel_2", wheel_2);

	engine->Run();

	delete engine;
	return 0;
}
