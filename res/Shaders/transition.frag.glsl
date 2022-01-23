#version 400

precision highp float;

in vec2             textureCoord;
uniform sampler2D   frameA;
uniform sampler2D   frameB;
uniform vec2        resolution;
uniform float       fader;
uniform float       time;

#define M2PI 1.57079632679
#define MPI1 3.14159265359
#define MPI2 6.28318530718

vec4 fade_mix()
{
    float exposure  = 1;

    float faderA    = clamp(1.0-fader*exposure, 0.0, 1.0);
    float faderB    = clamp(fader*exposure, 0.0, 1.0);

    vec4  t0        = texture2D(frameA, textureCoord) * faderA;
    vec4  t1        = texture2D(frameB, textureCoord) * faderB;

    return t1 + t0;
}

vec4 fade_color()
{
    float exposure  = 1;

    float faderA    = clamp(1.0-fader*exposure, 0.0, 1.0);
    float faderB    = clamp(fader*exposure, 0.0, 1.0);

    // Azul SEGA
//    vec4  t0        = texture2D(frameA, textureCoord) * clamp(vec4(1,2,4,1) * faderA, 0, 1);
//    vec4  t1        = texture2D(frameB, textureCoord) * clamp(vec4(1,2,4,1) * faderB, 0, 1);

    // Laranja
    vec4  t0        = texture2D(frameA, textureCoord) * clamp(vec4(2,4,1,1) * faderA, 0, 1);
    vec4  t1        = texture2D(frameB, textureCoord) * clamp(vec4(2,4,1,1) * faderB, 0, 1);

    return t0 + t1;// + vec4(0,0,0,1);// + t0; // mix(t0, t1, fader)
}

vec4 push()
{
    vec4 t0 = texture2D(frameA, (textureCoord / vec2(fader,1)) );
    vec4 t1 = texture2D(frameB, (textureCoord - vec2(fader,0)) / vec2(1-fader,1));

    return t0 + t1;
}

vec4 slide()
{
    vec4 t0 = texture2D(frameA, textureCoord + vec2(1-fader,0) );
    vec4 t1 = texture2D(frameB, textureCoord - vec2(fader,0) );

    return t0 + t1;
}

vec4 flip()
{
    float f = clamp(fader,0,1);
    vec4 t0 = texture2D(frameA, textureCoord);
    vec4 t1 = texture2D(frameB, (textureCoord - vec2(0.5)) * fader + vec2(0.5));

    return vec4(t0.rgb * (1.0-t1.a), 0) + t1;
}

vec4 persiana()
{
    float   ang     = 0;//-M2PI;// * fader;
    float   s       = sin(ang);
    float   c       = cos(ang);
    vec2    coord   = (textureCoord  * mat2(c,-s,s,c) - vec2(0.5)) * vec2(1, resolution.y/resolution.x);

    float   f       = clamp(fader/2,0,1);
    float   freq    = 20;

//    float   theta   = (coord.x * freq) -(f*3); // linear
    float   theta   = (sqrt(coord.x*coord.x + coord.y*coord.y)*freq) - (f*freq); // radial

    float   b1      = clamp((1.0+floor(theta)/freq)-(f*2), 0, 1); // mapa profundidade
    float   b2      = theta-floor(theta); // mapa progresso
    float   pulso   = b1 > b2 ? 0 : 1;

//    // normal
    vec4    t0      = texture(frameA, textureCoord) * (1.0-pulso);//smoothstep(-1,1,s1);
    vec4    t1      = texture(frameB, textureCoord) * pulso;//smoothstep(-1,1,-s1);

//     //com zoom
//     vec4    t0      = texture(frameA, (textureCoord - vec2(0.5)) * (1-fader) + vec2(0.5)) * (1-pulso);
//     vec4    t1      = texture(frameB, (textureCoord - vec2(0.5)) * (2-fader) + vec2(0.5)) * pulso;

    //return vec4(vec3(pulso), 1);
    return vec4(t0.rgba) + vec4(t1.rgba);
}

vec4 effect_threshold()
{
    vec4 t0 = texture(frameA, textureCoord);
    float luma = (t0.r * 0.2126 + t0.g * 0.7152 + t0.b * 0.0722);
    return vec4(vec3(smoothstep(0.25, 0.75, luma)), t0.a);
}

vec4 effect_pal_signal()
{
    float   ang     = 0;
    float   s       = sin(ang);
    float   c       = cos(ang);
    vec2    coord   = textureCoord * mat2(c,-s,s,c);

    vec3    rgb_in = texture(frameA, textureCoord).rgb;

//    vec3    yuv;
//    yuv[0] = t0.r * 0.299 + t0.g * 0.587 + t0.b * 0.114;
//    yuv[1] = yuv[0] - t0.b * 0.492;
//    yuv[2] = yuv[0] - t0.r * 0.877;

    mat3 rgb2yuv = mat3( 0.299,  0.587,  0.114,
                        -0.147, -0.289,  0.486,
                         0.615, -0.515, -0.100);

    vec3 yuv_out = rgb_in * rgb2yuv;

//
//    float theta1 = MPI2  + (MPI2 * coord.x) * (resolution.x/3);
//    float theta2 = MPI2  + (MPI2 * coord.y) * (resolution.y/3);

    coord *= resolution/2;

    float s1    = sin(MPI2 * 4.43361875 * coord.x)/2;
    float c1    = cos(MPI2 * 4.43361875 * coord.x)/2;

    yuv_out.g   *= s1; //-1 a +1 -> -0.5 à +0.5
    yuv_out.b   *= c1;

    float luma  = (yuv_out[0]) + (yuv_out[1] + yuv_out[2]);

    //----------------------------------------------------------------//

    vec3 yuv_in  = vec3(luma, luma * s1, luma * c1);

    mat3 yuv2rgb = mat3(1.0,  0.0,   1.14,
                        1.0, -0.394,-0.581,
                        1.0,  2.028, 0.0);

    vec3 rgb_out = yuv_in.rgb * yuv2rgb;


//    rgb_out = vec3(0.5) + vec3(0,yuv_out.g,0);
//    rgb_out = vec3(0.5) + vec3(0,yuv_out.g,yuv_out.b);

//    rgb_out = vec3(luma);

    return vec4(rgb_out, 1);//vec4(textureCoord.y < 0.5 ? rgb_out : rgb_in, 1);
}




const mat3 yiq_mat = mat3(0.2989, 0.5959, 0.2115,
                          0.5870, -0.2744, -0.5229,
                          0.1140, -0.3216, 0.3114);
vec3 rgb2yiq(vec3 col)
{
    return yiq_mat * col;
}

vec4 effect_ntsc_signal_encoder()
{
    // Portação baseada em:
    // http://www.mediafire.com/view/touakpcbs2ujqcp/ntsc-maister.shader

    const float PI                  = 3.14159265;
    const float CHROMA_MOD_FREQ     = 0.4 * PI;
    const float CHROMA_AMP          = 1.0;
    const float ENCODE_GAMMA        = 1.0 / 2.2;
    vec2        pix_no              = textureCoord*resolution;

    //-----------------------------//

    vec3    col             = texture2D(frameA, textureCoord).rgb;
    vec3    yiq             = rgb2yiq(pow(col, vec3(ENCODE_GAMMA)));
    float   chroma_phase    = PI * 0.6667 * (mod(pix_no.y, 3.0) + float(time*1000));
    float   mod_phase       = chroma_phase + pix_no.x * CHROMA_MOD_FREQ;
    float   i_mod           = CHROMA_AMP * cos(mod_phase);
    float   q_mod           = CHROMA_AMP * sin(mod_phase);

    yiq = vec3(yiq.x, yiq.y * i_mod, yiq.z * q_mod);

    return vec4(yiq, 1.0);
}

vec4 effect_chroma_key()
{
    vec3    rgb_input       = texture(frameA, textureCoord).rgb;

    //-------------------------------------------//

    float   gain_master     = 1;
    vec3    gain_channel    = vec3(1.0, 1.6, 1.0);
    vec3    gain_output     = rgb_input * gain_channel * gain_master;

    vec3    pos             = gain_output * vec3(0.0, 1.0, 0.0);
    vec3    neg             = gain_output * vec3(1.0, 0.0, 1.0);

    float   key             = (pos.r+pos.g+pos.b)-(neg.r+neg.g+neg.b);

//    return vec4(vec3(key), 1);
    return vec4(rgb_input, 1-key);
}

vec4 effect_blur()
{
    float blur_samples  = 100;

    float blur_length   = 100;
    float blur_step     = 1.0/blur_length;

    vec4  rgb_out;

    vec2 uv = 1.0/resolution;

    for(int i=0; i<blur_length; i++)
    {
        float x = blur_step * blur_length * uv.x * i;

        rgb_out += texture(frameA, textureCoord - vec2(x, 0));// * sin((MPI1/blur_length)*i);
    }

    rgb_out /= blur_length;

    rgb_out += texture(frameA, textureCoord).rgba;

    return rgb_out;
}

vec4 generator_rainbow()
{
    vec4 t0 = texture(frameA, textureCoord);
    vec4 t1 = texture(frameB, textureCoord);

    float theta = MPI2 * (1.0-textureCoord.x);
    vec3 phases = vec3(0, 0.5, 1) * MPI1;

    return vec4(0.5+0.5*cos(theta + phases), 1);
}

vec4 zoom_faixas()
{
    int qtd_faixas  = 30;
    float largura   = 1.0/qtd_faixas;

    vec4 rgb_out;
    vec4 rgb_last = vec4(0);
    vec4 rgb_current;

    for(int i=0; i<qtd_faixas; i++)
    {
        vec2 coord = (textureCoord - vec2(0.5)) * (1+i*fader) + vec2(0.5);

        if(coord.x > largura*i && coord.x < largura*(i+1))
            rgb_current = texture(frameA, coord);
        else
            rgb_current = vec4(vec3(0), 0);

        rgb_current *= vec4(vec3(1-rgb_last.a), 1);

        rgb_out += rgb_current;//vec4(vec3(rgb_current.a), 1);

        rgb_last = rgb_current;
    }

//    rgb_out.rgb *= 1-fader;

    return rgb_out;// / qtd_faixas;
}

//vec4 shake()
//{
//    float s10 = sin(MPI2 * 15325 * time) * 0.0;
//    float s11 = sin(MPI2 * 0.5 * time) * 0.1;
//
//    float s20 = sin(MPI2 * 60 * time) * 0.1;
//
//    return texture(frameA, textureCoord - vec2(s10, s20));
//}

void main()
{
    gl_FragData[0] = fade_color();
}

