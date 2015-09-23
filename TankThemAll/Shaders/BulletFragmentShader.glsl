#version 440 core

layout(location = 0) out vec4 out_color;

in vec4 color;

in vec3 Position_worldspace;
in vec3 Normal_cameraspace;
in vec3 EyeDirection_cameraspace;
in vec3 LightDirection2_cameraspace;

void main()
{
	vec3 LightColor = vec3(1,1,1);
	float LightPower2 = 120.0f;

	vec3 MaterialDiffuseColor = vec3(0.75,0.75,0.75);
	vec3 MaterialAmbientColor = vec3(0.4,0.4,0.4) * MaterialDiffuseColor;
	vec3 MaterialSpecularColor = vec3(0.6,0.6,0.6);

	float distance2 = 11.225;

	vec3 n = normalize( Normal_cameraspace );


	vec3 l2 = normalize( LightDirection2_cameraspace);

	
	float cosTheta2 = clamp( dot( n,l2 ), 0,1 );

	vec3 E = normalize(EyeDirection_cameraspace);

	vec3 R2 = reflect(-l2,n);

	float cosAlpha2 = clamp( dot( E,R2 ), 0,1 );

	out_color = 
		// Ambient : simulates indirect lighting
		vec4(MaterialAmbientColor +

		(MaterialDiffuseColor * LightColor * LightPower2 * cosTheta2 / (distance2*distance2)) +

		(MaterialSpecularColor * LightColor * LightPower2 * pow(cosAlpha2,5) / (distance2*distance2)),1);
}