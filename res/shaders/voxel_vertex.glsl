#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 in_uv;

uniform mat4 mvp;

out vec3 uv;

void main() 
{
    gl_Position = mvp * vec4(vertexPosition, 1.0);
    uv = in_uv;
}