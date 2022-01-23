#version 400

in vec2             texCoord;
uniform sampler2D   texAtlas;


vec4 render_oval(float x, float y, float radius, vec4 color)
{
    float r1 = sqrt( (pow(gl_FragCoord.x-(radius/2), 2) )  + (pow(gl_FragCoord.y-(radius/2), 92) * 1) );
    return r1 < radius/2 ? color : vec4(0,0,0,0);
}

vec4 render_rect(float x, float y, float width, float height, vec4 color)
{
    return
    gl_FragCoord.x >= x &&
    gl_FragCoord.x < x+width &&
    gl_FragCoord.y >= y &&
    gl_FragCoord.y < y+height ? color : vec4(0,0,0,0);
}

vec4 render_grad(vec4 color)
{
    float x = gl_FragCoord.x/700;
    return vec4(x);
}

void main()
{
    float x         = texture(texAtlas, texCoord).r;
    vec4 b_color    = vec4(0.75, 0, 0, 1);
    vec4 f_color    = vec4(0.75, 0.75, 0.75, 1);
    gl_FragColor    = b_color * vec4(1-x) + f_color * vec4(x);
    //gl_FragColor = vec4(vec3(1), x);

//    gl_FragColor = render_grad(b_color);
}
