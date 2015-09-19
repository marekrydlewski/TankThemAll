#version 440 core

layout(location = 0) out vec4 out_color;

in vec2 tex;

uniform sampler2D texture_grass;

void main()
{
	out_color = texture(texture_grass, tex);
}