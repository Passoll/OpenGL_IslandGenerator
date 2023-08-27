#version 460 core
layout(quads, fractional_odd_spacing, ccw) in;

//uniform sampler2D heightMap;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

//noise control
uniform int octave;
uniform float frequency;
uniform float offset;
uniform float amplitude;

in vec2 TextureCoord[];

out float Height;
out vec3 Normal;
out vec2 TexCoord;
out vec3 Position;

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

//fbm
float mountain_noise(vec2 p, int octave, vec2 rawp)
{
    float noise = 0;
    for (int i = 1; i <= octave; i++) {
        noise += perlin_noise(p * i) / i;
    }
    float tstep = smoothstep(0.0, 0.3, 0.5 - abs(rawp.x - 0.5))
        * smoothstep(0.0, 0.3, 0.5 - abs(rawp.y - 0.5));
    return clamp(noise, 0.02, 1.0) * tstep ;
}

void main()
{
    float u = gl_TessCoord.x;
    float v = gl_TessCoord.y;

    vec2 t00 = TextureCoord[0];
    vec2 t01 = TextureCoord[1];
    vec2 t10 = TextureCoord[2];
    vec2 t11 = TextureCoord[3];

    vec2 t0 = (t01 - t00) * u + t00;
    vec2 t1 = (t11 - t10) * u + t10;
    vec2 texCoord = (t1 - t0) * v + t0;
    vec2 rawTexCoord = texCoord;
    TexCoord = texCoord;

    //Height = texture(heightMap, texCoord).y * 64.0 - 16.0;
    texCoord = texCoord * frequency + offset;
    Height = mountain_noise(texCoord, octave, rawTexCoord);
    
    //calculate the normal
    float epsilon = 0.001;
    float Height_du = mountain_noise(texCoord + vec2(epsilon, 0.0), octave, rawTexCoord);
    float Height_dv = mountain_noise(texCoord + vec2(0.0, epsilon), octave, rawTexCoord);
    //cross tangent and bitangent
    Normal = normalize(vec3( (Height - Height_dv) / epsilon,
                                1,
                             (Height - Height_du) / epsilon ));

    Height = amplitude * Height * 64.0 - 16.0;
  
    vec4 p00 = gl_in[0].gl_Position;
    vec4 p01 = gl_in[1].gl_Position;
    vec4 p10 = gl_in[2].gl_Position;
    vec4 p11 = gl_in[3].gl_Position;

    vec4 uVec = p01 - p00;
    vec4 vVec = p10 - p00;
    vec4 normal = normalize(vec4(cross(vVec.xyz, uVec.xyz), 0));

    vec4 p0 = (p01 - p00) * u + p00;
    vec4 p1 = (p11 - p10) * u + p10;
    vec4 p = (p1 - p0) * v + p0 + normal * Height;

    Position = p.xyz;

    gl_Position = projection * view * model * p;
}