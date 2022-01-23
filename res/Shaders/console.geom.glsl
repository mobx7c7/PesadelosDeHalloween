// Autor: Marcelo de Oliveira Bittencourt:
// Data : 13/04/2015
// Baseado em: http://github.prideout.net/strings-inside-vertex-buffers/

#version 400

mat4 ortho(float left, float right, float top, float bottom, float near, float far)
{
    mat4 m = mat4(1);

    m[0][0] = 2/(right-left); // largura (right-left)
    m[1][1] = 2/(top-bottom); // altura  (top-bottom)
    m[2][2] = -2/(far-near);

    m[3][0] = -((right+left)/(right-left));
    m[3][1] = -((top+bottom)/(top-bottom));
    m[3][2] = -((far+near)/(far-near));

    return m;
}
mat4 translate(float x, float y)
{
    mat4 m = mat4(1);
    m[3][0] = x;
    m[3][1] = y;
    return m;
}
mat4 scale(float x, float y)
{
    mat4 m = mat4(1);
    m[0][0] = x;
    m[1][1] = y;
    return m;
}
mat4 rotate(float ang)
{
    mat4 m = mat4(1);
    float s = sin(ang);
    float c = cos(ang);
    m[0][0] = c;
    m[0][1] = s;
    m[1][0] = -s;
    m[1][1] = c;
    return m;
}

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

in int          v_character[1];
in int          v_index[1];
in ivec2        v_position[1];

uniform ivec2   resolution[1];
uniform ivec2   buffer_size[1];
uniform ivec2   atlas_size[1];
uniform ivec2   char_size[1];
uniform vec2    char_scale[1];

out vec2        texCoord;

void main()
{
    int letter  = clamp(v_character[0] - 32, 0, 223);

    int row     = letter / atlas_size[0].x + 1;
    int col     = letter % atlas_size[0].x;

    // valores normalizados
    float w     = 1.0/atlas_size[0].x;
    float h     = 1.0/atlas_size[0].y;

    // limites da textura
    float s0    = w * col;
    float t0    = 1.0 - h * row;
    float s1    = s0 + w;
    float t1    = t0 + h;

    mat4 m2     = mat4(1);
    m2[0][0]    = char_size[0].x * char_scale[0].x;             // scale
    m2[1][1]    = char_size[0].y * char_scale[0].y;             // scale
    m2[3][0]    = m2[0][0] * v_index[0];//mod(v_index[0], buffer_size[0].x);// translate
    m2[3][1]    = m2[1][1] * 0;//int(v_index[0]/buffer_size[0].x);         // translate

    // matriz de transformação
    mat4 mt;
    mt = ortho(0, resolution[0].x, resolution[0].y, 0, 0, 1);
    mt *= translate(v_position[0].x, v_position[0].y);
    //mt *= rotate(0.4);
    //mt *= translate(-200,0);
    mt *= m2;

    texCoord    = vec2(s0,t1); gl_Position = mt * vec4(0,0,0,1); EmitVertex();
    texCoord    = vec2(s1,t1); gl_Position = mt * vec4(1,0,0,1); EmitVertex();
    texCoord    = vec2(s0,t0); gl_Position = mt * vec4(0,1,0,1); EmitVertex();
    texCoord    = vec2(s1,t0); gl_Position = mt * vec4(1,1,0,1); EmitVertex();

    EndPrimitive();
}
