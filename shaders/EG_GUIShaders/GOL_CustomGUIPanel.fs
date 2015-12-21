#version 330

out vec4 FragColor;

float border = 3;

float lbrd1 = 600;
float lbrd2 = lbrd1 + border;

float rbrd2 = 800;
float rbrd1 = rbrd2 - border;

float hLine1 = 100;
float hLine2 = 200;
float hLine3 = 300;
float hLine4 = 400;
float hLine5 = 500;
float hLine6 = 600;

void main()
{
	vec2 fragCoord = gl_FragCoord.xy;

	bool bx = (lbrd1 <= fragCoord.x) && (fragCoord.x < lbrd2) || (rbrd1 <= fragCoord.x) && (fragCoord.x < rbrd2);
	bool by = (fragCoord.y == hLine1) 
	|| (fragCoord.y == hLine2) || (fragCoord.y == hLine3) || (fragCoord.y == hLine4) ;

//	int b = (int)(bx || by);	
//	FragColor = b * vec4(0.0,0.0,0.0,1.0) + (1-b) * vec4(1.0,1.0,1.0,1.0);


 	if(bx || by)
 		FragColor = vec4(0.0,0.0,0.0,1.0);
	else
	 	FragColor = vec4(1.0,1.0,1.0,1.0);


}