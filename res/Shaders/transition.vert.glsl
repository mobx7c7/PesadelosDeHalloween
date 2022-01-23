#version 400

#extension GL_ARB_explicit_uniform_location : enable

layout(location=10) in vec2      coord_vertex;
layout(location=11) in vec2      coord_texture;
layout(location=12) in vec3      coord_normal;
layout(location=13) in vec4      coord_color;
layout(location=4)  uniform mat4 m_src;
layout(location=5)  uniform mat4 m_dst;

out vec2 textureCoord;

void main()
{
    textureCoord = vec4(m_dst * vec4(coord_texture, 0, 1)).xy;
    gl_Position = m_src * vec4(coord_vertex, 0, 1);

}
