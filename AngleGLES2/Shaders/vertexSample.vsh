#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aCol;
out vec4 aColor;
flat out int AlphaTest;
flat out int AlphaTestMode;
out float AlphaReference;

uniform mat4 transform;
uniform int u_AlphaTest;
uniform int u_AlphaTestMode;
uniform float u_AlphaReference;

void main()
{
	gl_Position = transform * vec4(aPos, 1.0f);
	aColor = aCol;
	AlphaTest = u_AlphaTest;
	AlphaTestMode = u_AlphaTestMode;
	AlphaReference = u_AlphaReference;
}

