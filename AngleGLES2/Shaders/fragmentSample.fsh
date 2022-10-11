#version 330 core

in vec4 FogColor;
in float FogLinearStart;
in float FogLinearEnd;
in float FogDensity;
in float FogEquation;
flat in int FogIsEnabled;

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
	if(AlphaTest == 1)
	{
		switch(AlphaTestMode)
		{
			case 512:
				discard;
			break;
				
			case 513:
				if(aColor.a < AlphaReference)
				{
					outputColor = aColor;
				}
				else
				{
					discard;
				}
			break;
			
			case 514:
				if(aColor.a == AlphaReference)
				{
					outputColor = aColor;
				}
				else
				{
					discard;
				}
			break;
			
			case 515:
				if(aColor.a <= AlphaReference)
				{
					outputColor = aColor;
				}
				else
				{
					discard;
				}
			break;
			
			case 516:
				if(aColor.a > AlphaReference)
				{
					outputColor = aColor;
				}
				else
				{
					discard;
				}
			break;
			
			case 517:
				if(aColor.a != AlphaReference)
				{
					outputColor = aColor;
				}
				else
				{
					discard;
				}
			break;
			
			case 518:
				if(aColor.a >= AlphaReference)
				{
					outputColor = aColor;
				}
				else
				{
					discard;
				}
			break;
			
			case 519:
				outputColor = aColor;
			break;
		}
	}
	else
	{
		outputColor = aColor;
	}
	
	if(FogIsEnabled == 1)
	{
		float fogCoordinate = abs(EyeSpacePosition.z / EyeSpacePosition.w);
		outputColor = mix(outputColor, vec4(FogColor), getFogFactor(fogCoordinate));
	}
	
	gl_FragColor = outputColor;
}

