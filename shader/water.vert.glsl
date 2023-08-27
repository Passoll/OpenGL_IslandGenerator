#version 460 core
//No compute shader..
layout (location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;

out vec2 TexCoords;
out vec3 wPos;

uniform mat4 model;
uniform mat4 view;
uniform float iTime;
uniform mat4 projection;

void main()
{
    vec3 Pos = aPos;
    Pos.y += sin(iTime) * 0.00001;

    gl_Position = projection * view * model * vec4(Pos, 1.0f);

    wPos = (model * vec4(Pos, 1.0f)).xyz;
    TexCoords = aTexCoord;
}
