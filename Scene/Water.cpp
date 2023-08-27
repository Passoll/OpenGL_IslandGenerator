#include "Water.h"

float fresExp = 1;
Water::Water(float h, float s) {
    //postion
    this->scale = s;
    this->height = h;

    this->freq = 160;
    this->offset = 10;
    this->speed = 1;
    //shader
    this->_shader = new Shader("shader/water.vert.glsl", "shader/water.frag.glsl");

    this->geometry = new Plane();
    std::string path = "resources/Water.bmp";
    this->textureid[0] = loadtexture(path, 0);

    glBindTexture(GL_TEXTURE_2D, 0);

}

void Water::setGUI() {
    ImGui::Begin("Water controls: ");
    ImGui::SliderFloat("scale", (float*)&scale, 500.0f, 1000.0f); // Edit 3 floats representing a color 
    ImGui::SliderFloat("Height", (float*)&height, -1.f, 1.f);
    ImGui::SliderFloat("Frequency", (float*)&freq, -1.f, 500.f);
    ImGui::SliderFloat("Offset", (float*)&offset, -1.f, 30.f);
    ImGui::SliderFloat("speed", (float*)&speed, 0.f, 30.f);
    ImGui::SliderFloat("fresExp", (float*)&fresExp, 0.f, 30.f);
    ImGui::End();
}

void Water::draw(float time) {

    this->_shader->use();//activate

    // camera/view transformation
    glm::mat4 view = this->_sceneIF->cam->GetViewMatrix();
    this->_shader->setMat4("projection", this->_sceneIF->projMatrix);
    this->_shader->setMat4("view", view);

    glm::mat4 model = glm::mat4(1.0);
    model = glm::scale(model, glm::vec3(scale));
    model = glm::translate(model, glm::vec3(0, height/scale, 0));
    this->_shader->setMat4("model", model);

    this->_shader->setFloat("freq", freq);
    this->_shader->setFloat("offset", offset);
    this->_shader->setFloat("iTime", time);
    this->_shader->setFloat("speed", speed);
    this->_shader->setFloat("fresExp", fresExp);
    this->_shader->setVec3("camPos", this->_sceneIF->cam->Position);

    this->_shader->setTex2D("watermap", this->textureid[0], 0);

    this->geometry->render();

    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE0);
}

Water::~Water() {
    delete this->_shader;
    delete this->geometry;
}