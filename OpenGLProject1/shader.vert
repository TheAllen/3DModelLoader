#version 330 core\n

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
out vec4 vColor;
out vec2 TexCoord;

void main()
{
	gl_Position = projection * view * model * vec4(pos, 1.0);
	vColor = vec4(vec3(0.5f, 0.5f, 0.5f), 1.0f);
	TexCoord = tex;
}