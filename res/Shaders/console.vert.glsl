#version 400

layout(location=0) in int character;
uniform ivec2 position;

out int     v_character;
out int     v_index;
out ivec2    v_position;

void main()
{
    v_character = character;
    v_position  = position;
    v_index     = gl_VertexID;
}
