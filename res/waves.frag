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

mat2 rotateMat(float angle)
{
    float s = sin(angle);
    float c = cos(angle);
    return mat2(c, s, -s, c);
}

vec2 rotate(vec2 p, float angle)
{
    vec2 p2 = p + 0.5;

    mat2 m = rotateMat((360/MPI2) * angle);

    vec2 a1 = vec2(p2 * vec2(m[0][0], m[1][0]));
    vec2 a2 = vec2(p2 * vec2(m[0][1], m[1][1]));

    return vec2(a1.x + a1.y, a2.x + a2.y);
}


float gauss(float sigma, float position, float offset)
{
    float a = 1.0/sigma*sqrt(MPI2);
    return a * exp(-(pow(position - offset, 2)/2 * pow(sigma, 2)));
}



void main()
{
	float   phase   = (textureCoord.x * MPI2 * 8) + time;
	float   s1      = sin(phase);
	float   c1      = cos(phase);
	float   k0      = (c1+1.0/2.0) * 0.005;// * textureCoord.x;
	float   k1      = k0;
	vec4    pixel = texture2D(texture0, textureCoord + vec2(k0, k1));

//    pixel.r   += 0.0;
//    pixel.g   += 0.1;
//    pixel.b   += 0.2;
//    pixel.a   += 0.75;
//    pixel.rgb += s1 * 0.1;
//
//    pixel.a *= 1 - textureCoord.x;

    gl_FragColor = pixel * opacity;

//	vec4    sum;
//	vec2    dimension   = vec2(10, 20);
//	vec2    stepOffset  = vec2(1.0) / vec2(1280, 583);
//	for(int i=0; i<dimension.x+1; i++){
//        sum += texture2D(texture0, textureCoord - vec2(stepOffset.x * (i-(dimension.x/2)), 0.0));
//	}
//	sum /= dimension.x+1;
//
//	gl_FragColor = sum;
}

