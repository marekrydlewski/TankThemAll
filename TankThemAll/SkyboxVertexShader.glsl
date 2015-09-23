#version 440 core
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec2 in_tex;

uniform mat4 projection_matrix, view_matrix, model_matrix;

out vec2 tex;

void main()
{

	tex = in_color;
	gl_Position = projection_matrix * view_matrix * model_matrix * vec4(in_position, 1);
	
}