#version 330 core

out vec4 vertexColor;

layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos, 1.0);

    vertexColor = vec4(1.0, 0.0, 0.0, 0.0);
}