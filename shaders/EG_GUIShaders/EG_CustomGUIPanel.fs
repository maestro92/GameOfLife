#version 330

out vec4 FragColor;

void main()
{
/*
	vec2 fragCoord = gl_FragCoord.xy;

	bool bx = (fragCoord.x == 10);
	bool by = (fragCoord.y == 700);
*/
	FragColor = vec4(0.5, 0.5, 0.0, 1.0);
/*
 	if(bx && by)
 		FragColor = vec4(0.0,1.0,0.0,1.0);
	else
	 	FragColor = vec4(1.0,0.0,1.0,1.0);
	
*/
}