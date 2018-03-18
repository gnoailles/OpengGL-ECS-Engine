#shader vertex

#version 460

layout (location = 0) in vec3 i_position;
uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;

void main()
{
	gl_Position = u_proj * u_view * u_model * vec4(i_position, 1.0);
}



#shader fragment


#version 460
out vec4 color;

void main()
{
	color = vec4(0.8, 0.4, 0.2, 1);
}