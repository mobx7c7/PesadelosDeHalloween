#version 400

layout(location=10) in vec3      coord_vertex;
//layout(location=11) in vec2      coord_texture;
//layout(location=12) in vec3      coord_normal;
//layout(location=13) in vec4      coord_color;
layout(location=4)  uniform mat4 m_src;

void main()
{
    gl_Position = m_src * vec4(coord_vertex, 1);
}
