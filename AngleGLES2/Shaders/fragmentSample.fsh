#version 330 core

in vec4 FogColor;
in float FogLinearStart;
in float FogLinearEnd;
in float FogDensity;
in float FogEquation;
flat in int FogIsEnabled;
flat in int TextureIsEnabled;

uniform sampler2D u_texture;
in vec2 TexCoord;

float getFogFactor(float fogCoordinate);

float getFogFactor(float fogCoordinate)
{
	float result = 0.0;
	if(FogEquation == 0)
	{
		float fogLength = FogLinearEnd - FogLinearStart;
		result = (FogLinearEnd - fogCoordinate) / fogLength;
	}
	else if(FogEquation == 1) {
		result = exp(-FogDensity * fogCoordinate);
	}
	else if(FogEquation == 2) {
		result = exp(-pow(FogDensity * fogCoordinate, 2.0));
	}
	
	result = 1.0 - clamp(result, 0.0, 1.0);
	return result;
}


in vec4 aColor;
flat in int AlphaTest;
flat in int AlphaTestMode;
in float AlphaReference;
in vec4 EyeSpacePosition;


void main()
{
	vec4 outputColor;
	vec4 inputColor = aColor;
	if(TextureIsEnabled == 1)
	{
		inputColor = texture(u_texture, TexCoord);
	}
	if(AlphaTest == 1)
	{
		switch(AlphaTestMode)
		{
			case 512:
				discard;
			break;
				
			case 513:
				if(inputColor.a < AlphaReference)
				{
					outputColor = inputColor;
				}
				else
				{
					discard;
				}
			break;
			
			case 514:
				if(inputColor.a == AlphaReference)
				{
					outputColor = inputColor;
				}
				else
				{
					discard;
				}
			break;
			
			case 515:
				if(inputColor.a <= AlphaReference)
				{
					outputColor = inputColor;
				}
				else
				{
					discard;
				}
			break;
			
			case 516:
				if(inputColor.a > AlphaReference)
				{
					outputColor = inputColor;
				}
				else
				{
					discard;
				}
			break;
			
			case 517:
				if(inputColor.a != AlphaReference)
				{
					outputColor = inputColor;
				}
				else
				{
					discard;
				}
			break;
			
			case 518:
				if(inputColor.a >= AlphaReference)
				{
					outputColor = inputColor;
				}
				else
				{
					discard;
				}
			break;
			
			case 519:
				outputColor = inputColor;
			break;
		}
	}
	else
	{
		outputColor = inputColor;
	}
	
	if(FogIsEnabled == 1)
	{
		float fogCoordinate = abs(EyeSpacePosition.z / EyeSpacePosition.w);
		outputColor = mix(outputColor, vec4(FogColor), getFogFactor(fogCoordinate));
	}
	
	gl_FragColor = outputColor;
}

