#version 330

uniform sampler2D u_inputTexture;
uniform float u_startGridX;
uniform float u_startGridY;
uniform float u_endGridX;
uniform float u_endGridY;
uniform vec2 u_inputPosition;

in vec2 vf_UV;
out vec4 FragColor;

void main()
{
	vec2 fragCoord = gl_FragCoord.xy;
 	bool bx = (u_startGridX <= fragCoord.x) && (fragCoord.x <= u_endGridX);
 	bool by = (u_startGridY <= fragCoord.y) && (fragCoord.y <= u_endGridY);
 	if(bx && by)
 	{
 		FragColor = vec4(0.0,0.0,0.0,1.0);
 		return;
 	}

	vec2 tc = vf_UV;	 tc.y = 1.0 - tc.y;
	FragColor = texture(u_inputTexture, tc);



}


