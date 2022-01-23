#version 400

in vec2             textureCoord;
uniform sampler2D   texture0;
uniform sampler2D   texture1;
uniform sampler2D   texture2;
uniform sampler2D   texture3;
uniform float       opacity;
uniform float       mix;

#define MPI 3.14159265359
#define MPI2 6.28318530718

void main()
{
    vec4 t = texture2D(texture0, textureCoord);
//    vec4 t = texture2D(texture0, vec2(textureCoord.x, (-1.0*textureCoord.y)+1.0) );

//    vec3 phases = vec3(0.0, 0.5, 1.0) * MPI/2;
//    vec3 colors = vec3(abs(sin(textureCoord.x * MPI2 * 16 + phases)) );
//    float lumaKey = (pixel.r + pixel.g + pixel.b);
//    lumaKey *= 10;
//    lumaKey = min(max(0.15 + lumaKey, 0.0), 1.0);

    gl_FragColor = t * opacity;//vec4(colors, 1);//pixel;//vec4(pixel.rgb, lumaKey);
}

