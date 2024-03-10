#version 330 core

uniform vec4 albedo;

out vec4 color;

void main()
{
    color = albedo;
}