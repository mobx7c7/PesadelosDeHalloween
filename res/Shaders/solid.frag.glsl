#version 400

struct Rect
{
    float left;
    float top;
    float right;
    float bottom;
};

uniform Rect    rect[1];
uniform vec4    color;

#define M2PI 1.57079632679
#define MPI1 3.14159265359
#define MPI2 6.28318530718

float minmax(float value, float min_value, float max_value)
{
    return  min(max(value, min_value), max_value);
}
float toAng(float rad)
{
    return rad*(180/MPI1);
}
float toRad(float ang)
{
    return ang*(MPI1/180);
}
mat2 rotate(float rad)
{
    mat2 m      = mat2(1);
    float s     = sin(rad);
    float c     = cos(rad);
    m[0][0]     =  c;
    m[1][0]     =  s;
    m[0][1]     = -s;
    m[1][1]     =  c;
    return m;
}

mat2 ortho(float left, float right, float top, float bottom)
{
    mat2 m;
    m[0][0] = (right-left)/2;
    m[1][1] = (top-bottom)/2;
    return m;
}

//float rect_shape()
//{
//    vec2 p1 = vec2(0, 0);
//    vec2 p2 = vec2(100, 100);
//
//    bool recta = (gl_FragCoord.x > p1.x && gl_FragCoord.x < p2.x &&
//                  gl_FragCoord.y > p1.y && gl_FragCoord.y < p2.y);
//
//    float size = 1;
//    p1 += size;
//    p2 -= size;
//
//    bool rectb = (gl_FragCoord.x > p1.x && gl_FragCoord.x < p2.x &&
//                  gl_FragCoord.y > p1.y && gl_FragCoord.y < p2.y);
//
//    return recta && !rectb ? 1.0 : 0.0;
//}

float fill_rect_shape(vec2 p1, vec2 p2)
{
    vec2 dimension  = (p2-p1);
    // vec2 border     = dimension - 1;
    //return 1.0-(gl_FragCoord.x-border.x)/(dimension.x-border.x);

//    mat2  orth = ortho(0.0, 1.0/1280.0, 0.0 , 1.0/583.0);
//    p1 *= orth;
//    p2 *= orth;

    return
    gl_FragCoord.x > p1.x && gl_FragCoord.x < p2.x &&
    gl_FragCoord.y > p1.y && gl_FragCoord.y < p2.y ? 1.0 : 0.0;
}
float line_rect_shape(vec2 p1, vec2 p2)
{
    vec2 border = vec2(2);
    return fill_rect_shape(p1, p2) - fill_rect_shape(p1+border, p2-border);
}
float oval_shape(vec2 position)
{
    float   border      = 1;
    float   radius      = 100;
    vec2    offset      = gl_FragCoord.xy -position;// -vec2(radius);

    float   oval1       = sqrt(pow(offset.x, 2) + pow(offset.y, 2));
    float   border1     = radius-border;

    return  1.0-(oval1-border1)/(radius-border1);
}
float rsqr_shape(vec2 position, vec2 dimension) // round square
{
    float   border      = 2;
    float   radius      = 50;

    /*********************************************/
    float   diam        = radius*2;
    vec2    offset      = gl_FragCoord.xy - position - vec2(radius);

    offset.x            = min(offset.x, max(offset.x+diam-dimension.x, 0));
    offset.y            = min(offset.y, max(offset.y+diam-dimension.y, 0));

    float   oval1       = sqrt(pow(offset.x, 2) + pow(offset.y, 2));
    float   border1     = radius-border;

    return 1.0 - minmax((oval1-border1)/(radius-border1), 0.0, 1.0);
}
float sqr_grad(vec2 position)
{
    position        = vec2(300);

    mat2    rot     = rotate(toRad(45));
    vec2    fbuf    = vec2(1280, 583); // Nota: substituir por dimensão real do fbuf
    vec2    aspect  = vec2(fbuf.x/fbuf.y, 1.0);
    vec2    offset  = (gl_FragCoord.xy - position) * rot;

    vec2    border  = vec2(2) * aspect;

    //vec2    k       = (abs(offset)+border-fbuf)/border; //abs(offset)/dim.x;
    vec2    k       = abs(offset)/fbuf; //abs(offset)/dim.x;

    return 1.0 - minmax((k.x+k.y)/2, 0.0, 1.0);
}
float lin_grad(vec2 position)
{
    vec2 k = (gl_FragCoord.xy - position) * rotate(toRad(0));
    return 1.0 - minmax(abs(k.x)/400, 0.0, 1.0);
}
float line(vec2 p1, vec2 p2)
{
    vec2    dif     = p2-p1;
    float   ang     = -atan(dif.y, dif.x);

    vec2    offset  = (gl_FragCoord.xy - p1) * rotate(ang);
    float   dim     = 2;
    float   border  = 1;
    vec2    k       = (abs(offset) + border - dim)/border; //abs(offset)/dim.x;

    return 1.0 - minmax(k.y, 0.0, 1.0);
}

void main()
{
    //vec4 cor = vec4(1,0,0,1);
//    gl_FragData[0] = vec4(color.rgb, color.a * rect_shape(vec2(100, 100), vec2(200, 200)) ); //rsqr_shape(vec2(0, 0), vec2(400, 200))
//    gl_FragData[0] = vec4(color.rgb * line(vec2(0), vec2(100)), color.a); //rsqr_shape(vec2(0, 0), vec2(400, 200));

//    vec4 _color = color;
    float x = fill_rect_shape(vec2(rect[0].left, rect[0].top), vec2(rect[0].right, rect[0].bottom));
//    float x = oval_shape(vec2(100));
    gl_FragData[0] = color * vec4(vec3(x), 1);

//    ivec2 coord = ivec2(gl_FragCoord.xy);
//
//
//    if(coord.y%40 >= 20 ? coord.x%40 >= 20 : coord.x%40 < 20){
//        gl_FragData[0] = vec4(vec3(0.80),1);
//    }else{
//        gl_FragData[0] = vec4(vec3(0.85),1);
//    }
//
//    if(coord.x%40 == 0 || coord.y%40 == 0){
//        gl_FragData[0] = vec4(vec3(0.75),1);
////    }else if(coord.x%20 == 0 || coord.y%20 == 0){
////        gl_FragData[0] = vec4(vec3(0.80),1);
//    }else{
////        gl_FragData[0] = vec4(vec3(0.9),1);
//    }



}
