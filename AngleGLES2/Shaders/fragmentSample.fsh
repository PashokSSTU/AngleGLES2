#version 330 core
in vec4 aColor;
flat in int AlphaTest;
flat in int AlphaTestMode;
in float AlphaReference;

void main()
{
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
					gl_FragColor = aColor;
				}
				else
				{
					discard;
				}
			break;
			
			case 514:
				if(aColor.a == AlphaReference)
				{
					gl_FragColor = aColor;
				}
				else
				{
					discard;
				}
			break;
			
			case 515:
				if(aColor.a <= AlphaReference)
				{
					gl_FragColor = aColor;
				}
				else
				{
					discard;
				}
			break;
			
			case 516:
				if(aColor.a > AlphaReference)
				{
					gl_FragColor = aColor;
				}
				else
				{
					discard;
				}
			break;
			
			case 517:
				if(aColor.a != AlphaReference)
				{
					gl_FragColor = aColor;
				}
				else
				{
					discard;
				}
			break;
			
			case 518:
				if(aColor.a >= AlphaReference)
				{
					gl_FragColor = aColor;
				}
				else
				{
					discard;
				}
			break;
			
			case 519:
				gl_FragColor = aColor;
			break;
		}
	}
	else
	{
		gl_FragColor = aColor;
	}
}

