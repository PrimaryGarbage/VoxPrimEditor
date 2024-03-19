#version 330 core

layout(location = 0) in vec3 vertexPosition;

uniform mat4 mvp;

out vec3 uv;

void main() 
{
    gl_Position = mvp * vec4(vertexPosition, 1.0);
    uv = in_uv;
}