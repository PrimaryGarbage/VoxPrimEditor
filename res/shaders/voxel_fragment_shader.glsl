#version 330 core

in vec3 uv;

uniform vec4 albedo;

out vec4 color;

float isBorder()
{
    float borderWidth = 0.01;
    float firstEl = 0.0;
    float secondEl = 0.0;
    float thirdEl = 0.0;

    firstEl = step(1.0 - borderWidth, uv.x) + (1.0 - step(borderWidth, uv.x));
    secondEl = step(1.0 - borderWidth, uv.y) + (1.0 - step(borderWidth, uv.y));
    thirdEl = step(1.0 - borderWidth, uv.z) + (1.0 - step(borderWidth, uv.z));

    return clamp(firstEl * secondEl + firstEl * thirdEl + secondEl * thirdEl, 0.0, 1.0);
}

void main()
{
    vec4 borderColor = vec4(0.0, 0.0, 0.0, 1.0);

    float border = isBorder();

    color = albedo * (1.0 - border) + borderColor * border;
}