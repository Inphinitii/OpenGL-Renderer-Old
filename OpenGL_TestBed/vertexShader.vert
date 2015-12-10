#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 textureCoords;


uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

uniform vec4 color;

out vec4 inputColor;

void main()
{
	inputColor	= color;
	gl_Position = projection * view * model * vec4(position, 1.0);
}