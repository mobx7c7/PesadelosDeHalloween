#version 400

in vec2             textureCoord;
uniform sampler2D   textureObj;

void main()
{
    vec4 pixel = texture2D(textureObj, textureCoord);

    gl_FragColor = pixel;
}
