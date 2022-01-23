//#version 400
//
//layout(location=0) in int character;
//uniform ivec2 position;
//
//out int     v_character;
//out int     v_index;
//out ivec2   v_position;
//
//void main()
//{
//    v_character = character;
//    v_position  = position;
//    v_index     = gl_VertexID;
//}

#version 400

#extension GL_ARB_explicit_uniform_location : enable

layout(location=10) in vec2 coord_vertex;

layout(location=4) uniform mat4 m_src;
layout(location=5) uniform mat4 m_dst;

void main()
{
    gl_Position = m_src * vec4(coord_vertex, 0, 1);
}
