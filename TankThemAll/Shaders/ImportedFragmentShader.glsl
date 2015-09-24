#version 440 core

layout(location = 0) out vec4 out_color;

in vec2 tex;
in vec3 Position_worldspace;
in vec3 Normal_cameraspace;
in vec3 EyeDirection_cameraspace;
in vec3 LightDirection_cameraspace;
in vec3 LightDirection2_cameraspace;

uniform sampler2D texture_diffuse1;
uniform vec3 light_source_1;

void main()
{
	vec3 LightColor = vec3(1,1,1);
	float LightPower = 100.0f;
	float LightPower2 = 120.0f;

	vec3 MaterialDiffuseColor = texture2D( texture_diffuse1, tex ).rgb;
	vec3 MaterialAmbientColor = vec3(0.4,0.4,0.4) * MaterialDiffuseColor;
	vec3 MaterialSpecularColor = vec3(0.2,0.2,0.2);

	float distance = length( light_source_1 - Position_worldspace );
	float distance2 = 11.225;

	vec3 n = normalize( Normal_cameraspace );

	vec3 l = normalize( LightDirection_cameraspace );

	vec3 l2 = normalize( LightDirection2_cameraspace);

	float cosTheta = clamp( dot( n,l ), 0,1 );
	
	float cosTheta2 = clamp( dot( n,l2 ), 0,1 );

	vec3 E = normalize(EyeDirection_cameraspace);

	vec3 R = reflect(-l,n);
	vec3 R2 = reflect(-l2,n);

	float cosAlpha = clamp( dot( E,R ), 0,1 );
	float cosAlpha2 = clamp( dot( E,R2 ), 0,1 );

	out_color = 
		// Ambient : simulates indirect lighting
		vec4(MaterialAmbientColor +
		// Diffuse : "color" of the object
		(MaterialDiffuseColor * LightColor * LightPower * cosTheta / (distance*distance)) +
		// Specular : reflective highlight, like a mirror
		(MaterialSpecularColor * LightColor * LightPower * pow(cosAlpha,5) / (distance*distance)) +

		(MaterialDiffuseColor * LightColor * LightPower2 * cosTheta2 / (distance2*distance2)) +

		(MaterialSpecularColor * LightColor * LightPower2 * pow(cosAlpha2,5) / (distance2*distance2)),1);
}