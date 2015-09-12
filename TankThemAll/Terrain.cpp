#include "stdafx.h"
#include "Terrain.h"
#include <SOIL.h>

using namespace BasicEngine::Rendering::Models;

Terrain::Terrain()
{
}


Terrain::~Terrain()
{
}

void Terrain::Create(char *filename)
{
	unsigned char *data = SOIL_load_image(filename, &width, &height, &channels, SOIL_LOAD_L);

	heights = (float *)malloc(width *
		height *
		sizeof(float));

	normals = (float *)malloc(width *
		height *
		sizeof(float) * 3);

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			heights[i*width + j] = data[i*width + j] / 256.0;
		}

	ComputeNormals();

	SOIL_free_image_data(data);
}

void Terrain::ComputeNormals()
{

}