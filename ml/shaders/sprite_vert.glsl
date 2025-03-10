#version 330 core

layout (location = 0) in vec2 vertex;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 projection;
uniform mat4 model;

out vec2 TexCoord;

void main()
{
	TexCoord = aTexCoord;
	gl_Position =  projection * model * vec4(vertex.xy, 0.f, 1.f);
}