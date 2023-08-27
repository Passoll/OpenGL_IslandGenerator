#version 410 core

in float Height;
in vec3 Normal;
in vec2 TexCoord;
in vec3 Position;

out vec4 FragColor;

uniform sampler2D grass_map;
uniform sampler2D slope_map;
uniform sampler2D rock_map;
uniform sampler2D grass_aomap;
uniform sampler2D slope_aomap;
uniform sampler2D rock_aomap;

//uniform sampler2D detail_map;
uniform float Grassscale;
uniform float Rockscale;
uniform float trans_gs;
uniform float trans_sr;
uniform float grassRange;
uniform float slopeRange;
uniform float rockRange;
uniform vec3 lightPos;
uniform vec3 viewPos;
//uniform sampler2D grass_map;

vec2 hash22(vec2 p)//the gradient vector
{
    p = vec2(dot(p, vec2(127.1, 311.7)),
        dot(p, vec2(269.5, 183.3)));
    return  fract(sin(p) * 43758.5453123);
}
float perlin_noise(vec2 p)
{
    vec2 pi = floor(p);
    vec2 pf = p - pi;
    vec2 w = pf * pf * (3.0 - 2.0 * pf);
    return mix(mix(dot(hash22(pi + vec2(0.0, 0.0)), pf - vec2(0.0, 0.0)),
        dot(hash22(pi + vec2(1.0, 0.0)), pf - vec2(1.0, 0.0)), w.x),
        mix(dot(hash22(pi + vec2(0.0, 1.0)), pf - vec2(0.0, 1.0)),
            dot(hash22(pi + vec2(1.0, 1.0)), pf - vec2(1.0, 1.0)), w.x),
        w.y);
}

void main()
{
    if (Height < -14.8) {
        discard;
    }
    //vec3 lightDir = normalize(lightPos - fragPos);
  /*  vec4 grass_layer = texture(grass_map, TexCoord);
    vec4 rock_layer = texture(rock_map, TexCoord);
    vec4 sand_layer = texture(detail_map, TexCoord);*/
    float noise = perlin_noise(Position.xz * 0.1);
    vec2 RockTexCoord = TexCoord * Rockscale;
    //RockTexCoord.y /= Grassscale;
    vec2 grassTexCoord = TexCoord * Grassscale;
    vec4 m_grassColor = texture(grass_map, grassTexCoord) * texture(grass_aomap, grassTexCoord).r;
    vec4 l_grassColor = texture(grass_map, grassTexCoord * 0.2) * texture(grass_aomap, grassTexCoord * 0.2).r;
    vec4 s_grassColor = texture(grass_map, grassTexCoord * 5) * texture(grass_aomap, grassTexCoord * 5).r;
    
    vec4 grassColor = mix(m_grassColor, s_grassColor, 1.4 * perlin_noise(Position.xz * 0.2 + 22));
    grassColor = mix(grassColor, l_grassColor, 1.8* perlin_noise(Position.xz * 0.2 + 111));
    grassColor = texture(grass_map, grassTexCoord) * texture(grass_aomap, grassTexCoord).r;

    vec4 slopeColor = texture(slope_map, grassTexCoord) * texture(slope_aomap, grassTexCoord).r;
    vec4 rockColor = texture(rock_map, RockTexCoord) * texture(rock_aomap, RockTexCoord).r;

    float slope = 1 - Normal.y ;
    vec4 textureColor;

    if (slope < grassRange)
    {
        float blendAmount = slope / grassRange;
        blendAmount = pow(blendAmount, trans_gs);
        textureColor = mix(grassColor, slopeColor, blendAmount);
    }


    if ((slope < rockRange) && (slope >= grassRange))
    {
        float blendAmount = (slope - grassRange) * (1.0f / (slopeRange - grassRange));
        blendAmount = pow(blendAmount, trans_sr);
        textureColor = mix(slopeColor, rockColor, blendAmount);
    }

    if (slope >= rockRange)
    {
        textureColor = rockColor;
    }

    vec3 lightDir = normalize(vec3(1, 1, 1));
    float light =  clamp(dot(lightDir, Normal), 0.0, 1.0f) + 0.5  ;

    FragColor = textureColor * (noise * 0.4 + 0.7) * light;
    FragColor.w = 1;

    //FragColor = mix(col1, col2, Normal.y );
    //FragColor = vec4(Normal.x, Normal.y, Normal.z, 1);
}