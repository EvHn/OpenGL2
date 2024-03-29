#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 inColor;

out vec4 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);
    color = vec4(inColor, 1.0f);
}
