//
//  Include.h
//  Test_Ogl
//
//  Created by Passo Zhong on 2023/2/22.
//

#ifndef rd_imgui_h
#define rd_imgui_h

#include "../include/imgui/imgui.h"
#include "../include/imgui/imgui_impl_opengl3.h"
#include "../include/imgui/imgui_impl_glfw.h"
#include <iostream>

class Guicontroller
{
private:
    GLFWwindow* imwindow;
    ImVec4* clear_color;
    //param
    ImVec4* para3;
public:
    Guicontroller(GLFWwindow* window, ImVec4* para3 ): imwindow(window),  para3(para3)
    {
        ImGui::CreateContext();     // Setup Dear ImGui context
        ImGui::StyleColorsDark();       // Setup Dear ImGui style
        ImGui_ImplGlfw_InitForOpenGL(imwindow, true);     // Setup Platform/Renderer backends
        ImGui_ImplOpenGL3_Init("#version 410");
    }
    void LoopImGUI()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {

             ImGui::Begin("Control Panel");                          // Create a window called "Hello, world!" and append into it.
             ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
             ImGui::ColorEdit3("clear color", (float*)para3); // Edit 3 floats representing a color


             //ImGui::SameLine();
            
            
             ImGui::Text("Control Help");
             ImGui::Text("Direction Control: WASD QE");
             ImGui::Text("1 Wireframe Mode");
             ImGui::Text("2 FILL Mode");
             ImGui::End();
        }
    }
    
};



#endif /* Include_h */
