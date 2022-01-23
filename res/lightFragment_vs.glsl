#version 400

layout(location=0) in vec3      coord_vertex;
layout(location=1) in vec2      coord_texture;
layout(location=2) in vec3      coord_normal;
layout(location=3) in vec4      coord_color;
layout(location=4) uniform mat4 m_src;

uniform vec4 modelAmbient;
uniform vec4 matAmbient;
uniform vec4 matDiffuse;
uniform vec4 matSpecular;
uniform int  matShininess;
uniform vec4 lightPosition;
uniform vec4 lightAmbient;
uniform vec4 lightDiffuse;
uniform vec4 lightSpecular;
uniform vec3 lightSpotDirection;

out vec4 _modelAmbient;
out vec4 _matAmbient;
out vec4 _matDiffuse;
out vec4 _matSpecular;

out vec4 _lightPosition;
out vec4 _lightAmbient;
out vec4 _lightDiffuse;
out vec4 _lightSpecular;
out vec3 _lightSpotDirection;

out vec4 _ambient;
out vec3 _halfVector;
out vec3 _normal;

out vec2 _textureCoord;

void main()
{
    gl_Position     = m_src * vec4(coord_vertex, 1); //ftransform();

    //_normal         = normalize(gl_NormalMatrix * coord_normal);
    _normal         = normalize(coord_normal);
    _halfVector     = normalize(coord_vertex.xyz + lightPosition.xyz);
    _ambient        = lightAmbient * matAmbient + modelAmbient * matAmbient;
    _textureCoord   = coord_texture;

    _modelAmbient       = modelAmbient;
    _matAmbient         = matAmbient;
    _matDiffuse         = matDiffuse;
    _matSpecular        = matSpecular;
    _lightPosition      = lightPosition;
    _lightAmbient       = lightAmbient;
    _lightDiffuse       = lightDiffuse;
    _lightSpecular      = lightSpecular;
    _lightSpotDirection = lightSpotDirection;
}
