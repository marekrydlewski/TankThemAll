#version 440 core

layout(location = 0) out vec4 out_color;

in vec2 tex;

uniform sampler2D texture_diffuse1;

void main()
{
	out_color = texture(texture_diffuse1, tex);
}