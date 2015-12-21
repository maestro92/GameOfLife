#version 330
uniform sampler2D u_sourceTexture;

uniform int u_srcPresentValue;
uniform int u_srcEmptyValue;

uniform int u_dstPresentValue;
uniform int u_dstEmptyValue;


in vec2 vf_UV;
out vec4 FragColor;

/*
input -> simulation

in input
0.0 is present
1.0 is empty

in simulation
1.0 is present
0.0 is empty
*/

void main()
{
	vec2 tc = vf_UV;	 tc.y = 1.0 - tc.y;

	int value = int(texture(u_sourceTexture, tc).r);

	if(value == u_srcPresentValue)
		FragColor = vec4(u_dstPresentValue, u_dstPresentValue, u_dstPresentValue, 1.0);
	else
		FragColor = vec4(u_dstEmptyValue, u_dstEmptyValue, u_dstEmptyValue, 1.0);
}


