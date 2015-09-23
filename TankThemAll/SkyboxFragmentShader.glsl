#version 440 core

layout(location = 0) out vec4 out_color;

in vec2 tex;

uniform sampler2D skybox_texture;

void main()
{
 	out_color = texture2D(skybox_texture, tex);
}