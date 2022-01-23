#version 400

in vec2             textureCoord;
uniform sampler2D   frameA;
uniform sampler2D   frameB;
uniform float       mix;

vec4 blend_add()
{
    vec4 t0 = texture2D(frameA, textureCoord);
    vec4 t1 = texture2D(frameB, textureCoord);
    return (t0 * (1.0 - mix)) + (t1 * mix);
}

void main()
{
    gl_FragData[0] = blend_add();
}

