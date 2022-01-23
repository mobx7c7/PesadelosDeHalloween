#version 400

in vec2             textureCoord;
uniform sampler2D   texture0;
uniform sampler2D   texture1;
uniform sampler2D   texture2;
uniform sampler2D   texture3;
uniform float       opacity;
uniform float       mix;
uniform float       time;

#define MPI 3.14159265359
#define MPI2 6.28318530718

void main()
{
    vec2 tcoord = vec2(textureCoord.x, (-1.0*textureCoord.y)+1.0);

    vec4 pixel = texture2D(texture0, tcoord);

    float luma = (0.2126 * pixel.r  + 0.7152 * pixel.g + 0.0722 * pixel.b);

    gl_FragColor = vec4(vec3(luma), pixel.a) * opacity;
}
