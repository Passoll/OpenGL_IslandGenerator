#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../Scene/Camera.h"
#include <iostream>

extern bool drawterrain;
extern bool drawsky;
extern bool drawwater;
extern bool drawreflect;

class Window {
public:
	Window(unsigned int Width, unsigned int Height, bool& success);
	~Window();

	GLFWwindow* window;

	void processInput(float deltaTime);
	
	void setCam(Camera* cam) { camera = cam;};
	void terminate() {
		glfwTerminate();
	}

	void loopSwapBuffer() {
		glfwSwapBuffers(this->window);
		glfwPollEvents();
	}


private:
	static unsigned int W_Width;
	static unsigned int W_Height;

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static Camera* camera;

	static float lastX;
	static float lastY;
	static bool firstMouse;

	int oldState, newState;
	static bool mouseCursorDisabled;
};

