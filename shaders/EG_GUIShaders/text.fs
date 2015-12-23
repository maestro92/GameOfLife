#version 330

uniform sampler2D u_texture;
uniform vec3 u_color;

in vec2 vf_UV;
out vec4 FragColor;


void main()
{

	vec2 tc = vf_UV;	tc.y = 1.0 - tc.y;
	// pos = tc;

//	FragColor = texture(u_texture, tc);
//	FragColor = vec4(1, 1, 1, texture(u_texture, tc).r) * u_color;

	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(u_texture, tc).r);
	FragColor = vec4(u_color, 1.0) * sampled;
//	FragColor = texture(u_texture, tc);
/*
	if(gl_FragCoord.y > 200)
		FragColor = vec4(1.0, 0.0, 0.0, 1.0);
	else
		FragColor = vec4(0.0, 1.0, 0.0, 1.0);	
*/

	// FragColor = vec4(0.0, 1.0, 0.0, 1.0);
}



