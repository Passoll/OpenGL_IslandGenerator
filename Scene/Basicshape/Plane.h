#pragma once
#include <glad/glad.h>


class Plane
{
public:
    //This is available for multiple patch plane and single patch plane

    Plane();
    Plane(int res);
    void render();
    void render( const unsigned& amount);
    
    unsigned VAO = 0;
    unsigned VBO = 0;
    int rez;
    void renderPatch();

};