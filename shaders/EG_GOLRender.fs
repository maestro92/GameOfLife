#version 330
uniform sampler2D u_texture;
uniform vec2 Scale;

out vec4 FragColor;
	
void main()
{
 //   vec3 color = vec3(texture(u_texture, gl_FragCoord.xy));
 //   FragColor = vec4(color, 1.0);
 	FragColor = vec4(1.0,0.0,0.0,1.0);
}
