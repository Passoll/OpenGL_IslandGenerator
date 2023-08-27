#include "Skybox.h"

Skybox::Skybox() {
    //postion
    this->scale = 1000;
    this->height = 0;
    //shader
    this->_shader = new Shader("shader/skybox.vert.glsl", "shader/skybox.frag.glsl");

    this->geometry = new ibox();
    for (int i = 0; i < 5; ++i) {
        //texture
        std::string path = "resources/Skybox/SkyBox" + std::to_string(i) + std::string(".bmp");
        this->textureid[i] = loadSkytexture(path, 0);
      
    }
    glBindTexture(GL_TEXTURE_2D, 0);

}

void Skybox::setGUI() {
    ImGui::Begin("Sky controls: ");
    ImGui::SliderFloat("scale", (float*)&scale, 500.0f, 1000.0f);
    ImGui::SliderFloat("height", (float*)&height, 0.0f, 1000.0f);
    ImGui::End();
}

void Skybox::Flipdraw() {

    this->_shader->use();

    glm::mat4 model = glm::mat4(1.0);
    model = glm::scale(model, glm::vec3(scale, scale * 0.4, scale));
    model = glm::scale(model, glm::vec3(1, -1, 1));
    model = glm::translate(model, glm::vec3(0, 1, 0));
    this->_shader->setMat4("model", model);
    for (int i = 0; i < 5; ++i) {
        this->_shader->setTex2D(("skybox" + std::to_string(i + 1)).c_str(), this->textureid[i], i);
    }

    this->geometry->render();
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE0);
}

void Skybox::draw(float time) {

    this->_shader->use();//activate

    // camera/view transformation
    glm::mat4 view = this->_sceneIF->cam->GetViewMatrix();
    this->_shader->setMat4("projection", this->_sceneIF->projMatrix);
    this->_shader->setMat4("view", view);

    glm::mat4 model = glm::mat4(1.0);
    model = glm::scale(model, glm::vec3(scale, scale * 0.4, scale));
    model = glm::scale(model, glm::vec3(1, 1, 1));
    model = glm::translate(model, glm::vec3(0, 1, 0));
    this->_shader->setMat4("model", model);

    for (int i = 0; i < 5; ++i) {
        this->_shader->setTex2D(("skybox" + std::to_string(i + 1)).c_str(), this->textureid[i], i);
    }

    this->geometry->render();
    glBindTexture(GL_TEXTURE_2D, 0);

    glActiveTexture(GL_TEXTURE0);
}

Skybox::~Skybox() {
    delete this->_shader;
    delete this->geometry;
}