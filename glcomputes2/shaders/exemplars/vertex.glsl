
#version 100
attribute   highp   vec4	vtxCurrent;
uniform     mediump mat4	transform;

void main(void)
{
    gl_Position = transform * vtxCurrent;
}
