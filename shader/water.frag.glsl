#version 460 core

out vec4 FragColor;
in vec2 TexCoords;
in vec3 wPos;

uniform float freq;
uniform float offset;
uniform float iTime;
uniform float speed;
uniform float fresExp;
uniform vec3 camPos;

uniform sampler2D watermap;


void main()
{
    vec3 viewDir = normalize(wPos - camPos) ;

    vec2 uv1 = freq * TexCoords + iTime * speed * 0.01;
    vec4 mapColor = texture(watermap, uv1);
    
    float fresnel =  clamp( 1 - dot(vec3(0,1,0), viewDir), 0., 1.) /5 ;
    float dist = length(wPos - camPos);
    fresnel = pow(fresnel, fresExp);
    FragColor = (mapColor + fresnel + dist / 100) * 0.8;
    FragColor.w = 0.3;

}