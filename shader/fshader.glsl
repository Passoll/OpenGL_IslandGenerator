#version 410 core
#extension GL_EXT_gpu_shader4 : enable

out vec4 FragColor;
in vec3 noiseColor;
//in vec2 TexCoord;
uniform vec3 ourColor;
uniform bool toggle;
//
//uniform sampler2D texture_diffuse1;
//uniform sampler2D texture_diffuse2;
//uniform sampler2D texture_diffuse3;
//uniform sampler2D texture_specular1;
//uniform sampler2D texture_specular2;

void main()
{
    //FragColor = texture(texture_diffuse1, TexCoord);
    //FragColor =vec4(texture(texture_diffuse1, TexCoord).xyz,0);
   // FragColor =vec4(ourColor, 1.0f);
    if(toggle){
        FragColor =vec4(ourColor, 1.0f);
    }
    else{
        float r = (gl_PrimitiveID % 255) / 256.0f;
        //float g = ((gl_PrimitiveID + 20) % 256) / 256.0f;
        float g = (sin(gl_PrimitiveID / 100.0f) + 1)/2 ;
        //float b = ((gl_PrimitiveID + 100) % 256) / 256.0f;
        float b = (sin(gl_PrimitiveID/ 100.0f + 10) + 1)/2;
        
        FragColor =vec4(r,g,b, 1.0f);
    }
}
