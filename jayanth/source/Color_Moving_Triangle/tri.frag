#version 440 core

out vec4 color;

void main(void)
{
	color = vec4(sin(gl_FragCoord.x * 0.25) * 0.5 + 0.5,
                 cos(gl_FragCoord.x * 0.25) * 0.5 + 0.5,
                 sin(gl_FragCoord.x * 0.5) * 0.5 + 0.5,
                 1.0);
}      