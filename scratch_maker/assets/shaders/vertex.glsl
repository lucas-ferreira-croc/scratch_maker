#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 color;
layout(location = 2) in vec3 bottomPos;

out vec3 vertexColor;

uniform mat4 transform;

void main()
{	
	gl_Position = transform * vec4(pos, 1.0f);
	vertexColor = color;
}