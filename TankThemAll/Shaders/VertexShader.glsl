#version 450 core
 
void main(void)
{
   const vec4 vertices[6] = vec4[6](vec4( 0.25, -0.25, 0.5, 1.0),
                                    vec4(-0.25, -0.25, 0.5, 1.0),
                                    vec4( 0.25, 0.25, 0.5, 1.0),
									vec4( 0.35, 0.35, 0.55, 1.0),
									vec4( -0.35, -0.35, -0.5, 1.0),
									vec4( -0.35, 0.8, -0.5, 1.0));
									
   gl_Position = vertices[gl_VertexID];
}