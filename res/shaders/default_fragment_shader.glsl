#version 330 core

in vec3 uv;

uniform vec4 albedo;

out vec4 color;

void main()
{
    color = albedo;
}