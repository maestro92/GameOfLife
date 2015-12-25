#version 330

uniform sampler2D u_texture;
in vec2 vf_UV;

out vec4 FragColor;

void main()
{
	vec2 tc = vf_UV;	tc.y = 1.0 - tc.y;
	
	FragColor = texture(u_texture, tc);
//	FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}