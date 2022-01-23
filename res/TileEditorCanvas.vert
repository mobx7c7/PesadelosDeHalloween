#version 400

layout(location=0) attribute vec2   coord_vertex;
layout(location=1) attribute vec2   coord_texture;
layout(location=2) attribute vec3   coord_normal;
layout(location=3) attribute vec4   coord_color;
layout(location=4) uniform mat4     m_src;

out vec2 textureCoord;

void main()
{
    gl_Position = m_src * vec4(coord_vertex, 0, 1);
    textureCoord = coord_texture;
}
