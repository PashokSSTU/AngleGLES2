#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aCol;
layout (location = 2) in vec2 aTexCoord;
out vec4 aColor;
out vec2 TexCoord;
flat out int AlphaTest;
flat out int AlphaTestMode;
out float AlphaReference;
flat out int TextureIsEnabled;

out vec4 FogColor;
out float FogLinearStart;
out float FogLinearEnd;
out float FogDensity;
out float FogEquation;
flat out int FogIsEnabled;

out vec4 EyeSpacePosition;

uniform mat4 u_modelview;
uniform mat4 u_projection;

uniform int u_AlphaTest;
uniform int u_AlphaTestMode;
uniform float u_AlphaReference;
uniform vec4 u_FogColor;
uniform float u_FogLinearStart;
uniform float u_FogLinearEnd;
uniform float u_FogDensity;
uniform float u_FogEquation;
uniform int u_FogIsEnabled;

uniform int u_TextureIsEnabled;



void main()
{
	gl_Position = u_projection * u_modelview * vec4(aPos, 1.0f);
	aColor = aCol;
	AlphaTest = u_AlphaTest;
	AlphaTestMode = u_AlphaTestMode;
	AlphaReference = u_AlphaReference;
	EyeSpacePosition = u_modelview * vec4(aPos, 1.0f);
	
	FogColor = u_FogColor;
	FogLinearStart = u_FogLinearStart;
	FogLinearEnd = u_FogLinearEnd;
	FogDensity = u_FogDensity;
	FogEquation = u_FogEquation;
	FogIsEnabled = u_FogIsEnabled;
	
	TexCoord = aTexCoord;
	TextureIsEnabled = u_TextureIsEnabled;
}

