#version 440 core
layout (location = 0) in vec3 in_position;
layout (location = 1) in vec2 in_texture;
layout (location = 2) in vec3 in_normal;


out vec2 tex;
out vec3 Position_worldspace;
out vec3 EyeDirection_cameraspace;
out vec3 LightDirection_cameraspace;
out vec3 LightDirection2_cameraspace;
out vec3 Normal_cameraspace;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;
uniform vec3 light_source_1;

void main()
{
    gl_Position = projection_matrix * view_matrix * model_matrix * vec4(in_position, 1);

    Position_worldspace = (model_matrix * vec4(in_position, 1)).xyz;
	
	vec3 Position_cameraspace = (view_matrix * model_matrix * vec4(in_position ,1)).xyz;
	
	EyeDirection_cameraspace = vec3(0,0,0) - Position_cameraspace;
	
	vec3 LightPosition_cameraspace = (view_matrix * vec4(light_source_1, 1)).xyz;
	
	vec3 LightPosition2_cameraspace = (view_matrix * vec4((in_position + vec3(-5, 10, 1)),1)).xyz;

	LightDirection_cameraspace = LightPosition_cameraspace + EyeDirection_cameraspace;
	
	LightDirection2_cameraspace = LightPosition2_cameraspace + EyeDirection_cameraspace;

	Normal_cameraspace = (view_matrix * model_matrix * vec4(in_normal, 0)).xyz;
	
	tex = in_texture;
}