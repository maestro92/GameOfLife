#version 330

out vec4 FragColor;

uniform sampler2D u_sourceTexture;

void main()
{
    ivec2 T = ivec2(gl_FragCoord.xy);

    ivec2 oNW = ivec2(-1, 1),	oN = ivec2(0, 1),	oNE = ivec2(1, 1);
    ivec2 oW =  ivec2(-1, 0),	o =  ivec2(0, 0),	oE =  ivec2(1, 0);
  	ivec2 oSW = ivec2(-1, -1),	oS = ivec2(0, -1),	oSE = ivec2(1, -1);

    int pNW = int(texelFetchOffset(u_sourceTexture, T, 0, oNW).r);		
    int pN  = int(texelFetchOffset(u_sourceTexture, T, 0, oN).r);				
    int pNE = int(texelFetchOffset(u_sourceTexture, T, 0, oNE).r);		
    
    int pW  = int(texelFetchOffset(u_sourceTexture, T, 0, oW).r);		
    int p   = int(texelFetchOffset(u_sourceTexture, T, 0, o).r);		
    int pE  = int(texelFetchOffset(u_sourceTexture, T, 0, oE).r);		
    
    int pSW = int(texelFetchOffset(u_sourceTexture, T, 0, oSW).r);		
    int pS  = int(texelFetchOffset(u_sourceTexture, T, 0, oS).r);				
    int pSE = int(texelFetchOffset(u_sourceTexture, T, 0, oSE).r);		
    
    int sum = pNW + pN + pNE + pW + pE + pSW + pS + pSE;

    if(T.x <= 10)
    	FragColor = vec4(0.0, 1.0, 0.0, 1.0);
    else
    	FragColor = vec4(1.0, 1.0, 1.0, 1.0);
/*
    if(p == 1)
	{
		if(sum == 3 || sum == 2)
	    {
	   		FragColor = vec4(1.0, 1.0, 1.0, 1.0);    	
	    }

	    // under population and over population
	    else
	    {
	   		FragColor = vec4(0.0, 0.0, 0.0, 1.0);
	    }	
		
	}
	else
	{
		if(sum == 3)
		{
			FragColor = vec4(1.0, 1.0, 1.0, 1.0);
		}
	}
*/

}