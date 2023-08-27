#include <iostream>

// GLAD

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Scene/Skybox.h"
#include "Scene/Water.h"
#include "Scene/Terrain.h"
#include "Scene/Camera.h"

#include "Engine/Shader.h"
#include "Engine/rd_imgui.h"
#include "Engine/Windows.h"

//stb_image reader
#define STB_IMAGE_IMPLEMENTATION
#include "include/stb_image.h"

bool left_button = false;
bool sptoggle = false;
// Function prototypes
const GLuint W_WIDTH = 1500, W_HEIGHT = 1200;

//transform
float xRot_triangle = 0.0f;
float yRot_triangle = 0.0f;
float x_translate = 0.0f;

// camera
Camera camera(glm::vec3(0.0f, 1.0f, 0.0f));
float lastX = W_WIDTH / 2.0f;
float lastY = W_HEIGHT / 2.0f;
bool firstMouse = true;

glm::vec3 linecolor = glm::vec3(0.5f, 0.5f, 0.5f);
// Window dimensions

// timing
float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;

bool drawterrain = true;
bool drawsky = true;
bool drawwater = true;
bool drawreflect = true;


// The MAIN function, from here we start the application and run the game loop
int main()
{
    //-----------------------  Init GLFW window
    bool success = true;
    Window T_window = Window(W_WIDTH, W_HEIGHT, success);
    if (!success) return -1;

    T_window.setCam(&camera);
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    
    //------------------------------ Shader
    
    
    //------------------------------ Geometry
    // Set up vertex data (and buffer(s)) and attribute pointers
  
    
    //----------------------------- Buffer
    GLuint VBO, VAO, EBO;
 
    stbi_set_flip_vertically_on_load(true);
    
    //ourShader.setInt("texture", 0);//set the uniform

    static ImVec4 para3 = ImVec4(0.f, 0.f, 0.f, 1.00f);
    
    Guicontroller rd_imgui = Guicontroller(T_window.window, &para3);

    SceneInfo* sceneinfo = new SceneInfo();
    sceneinfo->projMatrix = glm::perspective(glm::radians(camera.Zoom), (float)W_WIDTH / (float)W_HEIGHT, 0.1f, 2000.0f);
    sceneinfo->cam = &camera;
    Skybox _sky = Skybox();
    Water _water = Water();
    Terrain _terrain = Terrain();

    _terrain._sceneIF = sceneinfo;
    _sky._sceneIF = sceneinfo;
    _water._sceneIF = sceneinfo;
    
    
    // Renderloop
    while (!glfwWindowShouldClose(T_window.window))
    {
       
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        T_window.processInput(deltaTime);
        rd_imgui.LoopImGUI();
       
        // Render
        glClearColor(para3.x,para3.y,para3.z,para3.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);//

        if (drawterrain) {
            glStencilFunc(GL_ALWAYS, 1, 0x00);
            glStencilMask(0x00);
            _terrain.draw(currentFrame);
            _terrain.setGui();
        }
        
        if (drawsky) {
            glStencilFunc(GL_ALWAYS, 1, 0x00);
            glStencilMask(0x00);
            _sky.draw(currentFrame);
            _sky.setGUI();
        }

        if (drawwater) {
            glStencilFunc(GL_ALWAYS, 1, 0xFF);
            glStencilMask(0xFF);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            _water.draw(currentFrame);
            _water.setGUI();
        }
        
        glClear( GL_DEPTH_BUFFER_BIT );

        //reflect
        if (drawreflect) {
            glStencilFunc(GL_EQUAL, 1, 0xFF);
            glStencilMask(0x00);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            glDepthFunc(GL_LEQUAL);
            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
            glDisable(GL_CULL_FACE);
            _terrain.Flipdraw();

            glStencilFunc(GL_EQUAL, 1, 0xFF);
            glStencilMask(0x00);
            glDepthFunc(GL_LESS);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            _sky.Flipdraw();

            _water.draw(currentFrame);
            glDisable(GL_BLEND);

            glStencilMask(0xFF);
            glStencilFunc(GL_ALWAYS, 0, 0xFF);

        }
      
        
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glBindVertexArray(0);
       
        // Swap the screen buffers + poll IO events
        T_window.loopSwapBuffer();
    }
    // Properly de-allocate all resources once they've outlived their purpose
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    
    
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    delete sceneinfo;
    // Terminate GLFW, clearing any resources allocated by GLFW.
    //glfwTerminate();
    return 0;
}


