#shader vertex

#version 460

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texCoord;

out vec4 v_color;
out vec2 v_texCoord;

void main()
{
	gl_Position = vec4(position, 1.0);
	v_color = color;
	v_texCoord = texCoord;
}



#shader fragment


#version 460
in vec4 v_color;
in vec2 v_texCoord;

uniform sampler2D u_texture;

out vec4 finalColor;

void main()
{
	finalColor = texture(u_texture, v_texCoord) * v_color;
}