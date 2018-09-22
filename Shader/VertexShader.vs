#version 330 core

uniform vec4 m_texture;
uniform vec4 m_color;
uniform vec4 m_ambientColorMaterial;
uniform vec4 m_emissionColorMaterial;
uniform vec4 m_ambientColorLightning;
uniform vec4 m_emissionColorLightning;
uniform vec4 m_specularColorLightning;
uniform vec4 m_diffuseColorLightning;

out vec4 vertexColor;

layout (location = 0) in vec3 m_pos;

void main()
{
    gl_Position = vec4(m_pos, 1.0);

    vertexColor = m_color;
}