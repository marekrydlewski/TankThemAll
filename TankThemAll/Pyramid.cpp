#include "stdafx.h"
#include "Pyramid.h"

using namespace BasicEngine;
using namespace Rendering;
using namespace Models;


Pyramid::Pyramid()
{
}


Pyramid::~Pyramid()
{
}


void Pyramid::Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix)
{
	for (auto& pyramid : listOfPyramid)
	{
		pyramid->Draw(projection_matrix, view_matrix);
	}

}

void Pyramid::Update()
{
	for (auto& pyramid : listOfPyramid)
	{
		pyramid->Update();
	}
}


void Pyramid::Create()
{
	for (int i = 0; i < 5; i++)
	{
		int XorZ = rand() % 2;
		int signX = rand() % 2 ? 1 : -1;
		int signZ = rand() % 2 ? 1 : -1;
		GLfloat Xoffset = ((((float)rand()) / (float)RAND_MAX) * (signX * 50 - signX * 3)) + signX * 3;
		GLfloat Zoffset = ((((float)rand()) / (float)RAND_MAX) * (signZ * 50 - signZ * 3)) + signZ * 3;
		for (int j = 0; j < 4; j++)
		{
			CubeIndex* box = new CubeIndex();
			XorZ == 0 ? box->Create(Xoffset + j * 2, 0, Zoffset) : box->Create(Xoffset, 0, Zoffset + j * 2);
			box->SetProgram(this->program);
			std::string tmp = "";
			sprintf((char*)tmp.c_str(), "bunch_%d_box_%d", i, j);
		}
		for (int j = 0; j < 3; j++)
		{
			CubeIndex* box = new CubeIndex();
			XorZ == 0 ? box->Create(Xoffset + 1 + j * 2, 2, Zoffset) : box->Create(Xoffset, 2, Zoffset + 1 + j * 2);
			box->SetProgram(this->program);
			std::string tmp = "";
			sprintf((char*)tmp.c_str(), "bunch_%d_box_%d", i, j + 4);
		}
		for (int j = 0; j < 2; j++)
		{
			CubeIndex* box = new CubeIndex();
			XorZ == 0 ? box->Create(Xoffset + 2 + j * 2, 4, Zoffset) : box->Create(Xoffset, 4, Zoffset + 2 + j * 2);
			box->SetProgram(this->program);
			std::string tmp = "";
			sprintf((char*)tmp.c_str(), "bunch_%d_box_%d", i, j + 7);
		}
		CubeIndex* box = new CubeIndex();
		XorZ == 0 ? box->Create(Xoffset + 3, 6, Zoffset) : box->Create(Xoffset, 6, Zoffset + 3);
		box->SetProgram(this->program);
		std::string tmp = "";
		sprintf((char*)tmp.c_str(), "bunch_%d_box_9", i);
	}
}