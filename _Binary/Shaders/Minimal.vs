#version 330
in vec3 positionBuffer;
void main()
{
	gl_Position = vec4( positionBuffer, 1.0 );
}