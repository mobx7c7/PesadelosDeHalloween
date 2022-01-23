#version 400

uniform int  matShininess;

//struct Material
//{
//    vec4 ambient;
//    vec4 diffuse;
//    vec4 specular;
//}
//struct Light
//{
//    vec4 spotDirection;
//    vec4 position;
//
//    vec4 ambient;
//    vec4 diffuse;
//    vec4 specular;
//}

in vec4 _modelAmbient;

in vec4 _matAmbient;
in vec4 _matDiffuse;
in vec4 _matSpecular;

in vec4 _lightPosition;
in vec4 _lightAmbient;
in vec4 _lightDiffuse;
in vec4 _lightSpecular;
in vec3 _lightSpotDirection;

in vec4 _ambient;
in vec3 _halfVector;
in vec3 _normal;

in vec2  _textureCoord;

uniform sampler2D texture0;

void main()
{
    vec3 normal = normalize(_normal);

    vec4 _diffuse  = _lightDiffuse  * _matDiffuse  * dot(normal, _lightSpotDirection);
    vec4 _specular = _lightSpecular * _matSpecular * pow(dot(normal, _halfVector), matShininess);
    vec4 _ambient  = _lightSpecular * _matAmbient  + _modelAmbient * _matAmbient;

    gl_FragColor = _diffuse + _ambient + _specular + texture2D(texture0, _textureCoord); //vec4(_normal, 1);
}
