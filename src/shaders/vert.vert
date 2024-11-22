#version 330 core
#extension GL_ARB_explicit_uniform_location : require
layout (location = 0) in vec3 position;
uniform mat4 mvp;
void main()
{
    gl_Position = vec4(position, 1.0);
}