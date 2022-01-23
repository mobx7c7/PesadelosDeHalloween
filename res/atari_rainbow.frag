#version 400

in vec2             textureCoord;
uniform sampler2D   texture0;
uniform sampler2D   texture1;
uniform sampler2D   texture2;
uniform sampler2D   texture3;
uniform float       opacity;
uniform float       mix;
uniform float       time;

void main()
{
    vec3 cor;

    switch(int(mod(time * 30, 4)))
    {
        case 1:
            cor = vec3(1,0,0);
            break;
        case 2:
            cor = vec3(0,1,0);
            break;
        case 3:
            cor = vec3(0,1,1);
            break;
        default:
            cor = vec3(1);
    }

    vec4 t = texture(texture0, textureCoord);

    gl_FragData[0] = t + vec4(cor, t.a);
}
