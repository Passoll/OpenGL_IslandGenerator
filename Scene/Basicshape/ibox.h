#pragma once
#include <glad/glad.h>

class ibox
{
public:

    ibox();
    void render();
    //void render(const unsigned& amount);

    unsigned VAO = 0;
    unsigned VBO = 0;

};