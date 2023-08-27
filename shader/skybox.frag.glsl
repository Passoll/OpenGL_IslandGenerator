#version 460 core

out vec4 FragColor;
in vec3 TexCoords;

uniform sampler2D skybox1;//right 
uniform sampler2D skybox2;//front
uniform sampler2D skybox3;//left 
uniform sampler2D skybox4;//back 
uniform sampler2D skybox5;//up


void main()
{
    vec3 v_TexCoord = TexCoords;
    if (abs(v_TexCoord.x - 1) < 0.001) {
        FragColor = texture(skybox1, (v_TexCoord.zy + 1.0) / 2.0);
    }
    else if (abs(v_TexCoord.z - 1) < 0.001) {
        FragColor = texture(skybox2, ( vec2( -v_TexCoord.x, v_TexCoord.y) + 1.0) / 2.0);
    }
    else if (abs(v_TexCoord.x + 1) < 0.001) {
        FragColor = texture(skybox3, (vec2(-v_TexCoord.z, v_TexCoord.y) + 1.0) / 2.0);
    }
    else if (abs(v_TexCoord.z + 1) < 0.001) {
        FragColor = texture(skybox4, (v_TexCoord.xy + 1.0) / 2.0);
    }
    else if (abs(v_TexCoord.y - 1) < 0.001) {
        FragColor = texture(skybox5, ( vec2( v_TexCoord.z, -v_TexCoord.x ) + 1.0) / 2.0);
    }
    else
        FragColor = vec4(0);
   
    FragColor.w = 0.5;

}