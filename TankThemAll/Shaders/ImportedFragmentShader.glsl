#version 440 core

layout(location = 0) out vec4 color;

in vec2 texture;

uniform sampler2D texture_diffuse1;

void main()
{
	color = texture(texture_diffuse1, texture);
}