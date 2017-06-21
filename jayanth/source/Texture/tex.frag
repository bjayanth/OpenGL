#version 440 core

out vec4 FragColor;

in vec3 fragcolor;
in vec2 texposn;

uniform sampler2D texture1;

void main(void)
{
    FragColor =  texture(texture1, texposn);
}      