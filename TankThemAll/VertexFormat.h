#pragma once
#include "stdafx.h"

using namespace glm;

struct VertexFormat
{
	vec3 position;

	VertexFormat(const vec3 &pos)
	{
		position = pos;
	}

};

