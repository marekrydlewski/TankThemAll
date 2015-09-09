#version 440 core
layout (location = 0) in vec3 in_position;
layout (location = 1) in vec2 in_texture;
//layout (location = 2) in vec3 in_normal;


out vec2 texture;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

void main()
{
    gl_Position = projection_matrix * view_matrix * model_matrix * vec4(in_position, 1);
    texture = in_texture;
}