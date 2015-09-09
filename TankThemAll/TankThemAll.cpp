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

	//Diamond* diamond = new Diamond();
	//diamond->SetProgram(engine->GetShader_Manager()->GetShader("cubeShader"));
	//diamond->Create();

	//engine->GetModels_Manager()->SetModel("diamond", diamond);

	engine->GetShader_Manager()->CreateProgram("importedModelShader",
		"Shaders\\ImportedVertexShader.glsl",
		"Shaders\\ImportedFragmentShader.glsl");

	/*ImportedModel* tank = new ImportedModel();
	tank->SetProgram(engine->GetShader_Manager()->GetShader("importedModelShader"));
	tank->Create("C:\\Projekty\\TankThemAll\\models\\Tiger\\Tiger_I.obj");

	engine->GetModels_Manager()->SetModel("tank", tank);*/


	std::vector<VertexFormat> vertices;
	std::vector<GLuint>  indices = { 0, 1, 2,   //upfront
		3, 4, 5,   //upright
		6, 7, 8,  //upback
		9, 10, 11,  //upleft
		12, 13, 14,  //lowfront
		15, 16, 17, //lowright
		18, 19, 20, //lowleft
		21, 22, 23 }; //lowback

	//upfront
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 0, 1.0), glm::vec4(0, 0, 1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(0, 1.0, 0), glm::vec4(1, 0, 1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 0, 1.0), glm::vec4(1, 1, 1, 1)));

	//upright
	vertices.push_back(VertexFormat(glm::vec3(1.0, 0, 1.0), glm::vec4(1, 1, 1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(0, 1.0, 0), glm::vec4(1, 1, 0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 0, -1.0), glm::vec4(1, 0, 0, 1)));

	//upback
	vertices.push_back(VertexFormat(glm::vec3(1.0, 0, -1.0), glm::vec4(0, 0, 0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(0, 1.0, 0), glm::vec4(1, 0, 0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 0, -1.0), glm::vec4(1, 1, 0, 1)));

	//upleft
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 0, -1.0), glm::vec4(0, 0, 0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(0, 1.0, 0), glm::vec4(0, 0, 1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 0, 1.0), glm::vec4(0, 1, 1, 1)));

	//lowfront
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 0, 1.0), glm::vec4(1, 1, 1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(0, -1.0, 0), glm::vec4(1, 0, 0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 0, 1.0), glm::vec4(1, 0, 1, 1)));


	//lowright
	vertices.push_back(VertexFormat(glm::vec3(1.0, 0, 1.0), glm::vec4(0, 0, 0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(0, -1.0, 0), glm::vec4(1, 0, 0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 0, -1.0), glm::vec4(1, 0, 1, 1)));

	//lowback
	vertices.push_back(VertexFormat(glm::vec3(1.0, 0, -1.0), glm::vec4(0, 0, 0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(0, -1.0, 0), glm::vec4(0, 0, 1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 0, -1.0), glm::vec4(0, 1, 1, 1)));

	//lowleft
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 0, -1.0), glm::vec4(1, 1, 1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(0, -1.0, 0), glm::vec4(1, 1, 0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 0, 1.0), glm::vec4(1, 0, 0, 1)));

	std::vector<TextureWrap> textures;

	Mesh* diamondMesh = new Mesh(vertices, indices, textures);
	diamondMesh->SetProgram(engine->GetShader_Manager()->GetShader("cubeShader"));

	engine->GetModels_Manager()->SetModel("diamondMesh", diamondMesh);

	engine->Run();

	delete engine;
	return 0;
}
