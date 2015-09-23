#version 440 core

layout(location = 0) out vec4 out_color;

in vec3 tex;

uniform samplerCube skybox_texture;

void main()
{
 	out_color = texture(skybox_texture, tex);
}