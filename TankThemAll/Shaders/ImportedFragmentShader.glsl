#version 440 core

layout(location = 0) out vec4 out_color;

in vec2 tex;
in vec3 Position_worldspace;
in vec3 Normal_cameraspace;
in vec3 EyeDirection_cameraspace;
in vec3 LightDirection_cameraspace;

uniform sampler2D texture_diffuse1;
uniform vec3 light_source_1;

void main()
{
	vec3 LightColor = vec3(1,1,1);
	float LightPower = 40.0f;

	vec3 MaterialDiffuseColor = texture2D( texture_diffuse1, tex ).rgb;
	vec3 MaterialAmbientColor = vec3(0.3,0.3,0.3) * MaterialDiffuseColor;
	vec3 MaterialSpecularColor = vec3(0.2,0.2,0.2);

	float distance = length( light_source_1 - Position_worldspace );

	vec3 n = normalize( Normal_cameraspace );

	vec3 l = normalize( LightDirection_cameraspace );

	float cosTheta = clamp( dot( n,l ), 0,1 );
	

	vec3 E = normalize(EyeDirection_cameraspace);

	vec3 R = reflect(-l,n);

	float cosAlpha = clamp( dot( E,R ), 0,1 );

	out_color = 
		// Ambient : simulates indirect lighting
		vec4(MaterialAmbientColor +
		// Diffuse : "color" of the object
		(MaterialDiffuseColor * LightColor * LightPower * cosTheta / (distance*distance)) +
		// Specular : reflective highlight, like a mirror
		(MaterialSpecularColor * LightColor * LightPower * pow(cosAlpha,5) / (distance*distance)),1);
}