#include "Windows.h"

unsigned int Window::W_Width = 1600;
unsigned int Window::W_Height = 800;

float Window::lastX = W_Width / 2.0f;
float Window::lastY = W_Height / 2.0f;
bool Window::firstMouse = true;
bool Window::mouseCursorDisabled = true;

Camera* Window::camera = 0;


Window::Window(unsigned int Width, unsigned int Height, bool& success) {

    this->W_Width = Width;
    this->W_Height = Height;
   
    //-----------------------  Init GLFW window
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    this->window = glfwCreateWindow(Width, Height, "My_Terrain", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    // Set the required callback functions
    // callback func: no move then use this,safer
    glfwSetFramebufferSizeCallback(this->window, framebuffer_size_callback);//viewport and buffer match
    glfwSetCursorPosCallback(this->window, mouse_callback);
    glfwSetScrollCallback(this->window, scroll_callback);
    glfwSetMouseButtonCallback(this->window, mouse_button_callback);


    // Initialize GLAD to setup the OpenGL Function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize glad" << std::endl;
        success = false;
    }
    else {
        std::cout << "Success to initialize glad" << std::endl;
        success = true;
    }

   

}



void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

//mouse
void Window::mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;
    if (!mouseCursorDisabled)
        Window::camera->ProcessMouseMovement(xoffset, yoffset);
}

void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        switch (button)
        {
        case GLFW_MOUSE_BUTTON_LEFT:
            break;
        case GLFW_MOUSE_BUTTON_MIDDLE:
            break;
        case GLFW_MOUSE_BUTTON_RIGHT:
            break;
        default:
            return;
        }
    }
    else {

    }
    return;
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void Window::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera->ProcessMouseScroll(static_cast<float>(yoffset));
}


void Window::processInput(float deltaTime)
{
    //move
    if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(this->window, true);
    if (glfwGetKey(this->window, GLFW_KEY_1) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (glfwGetKey(this->window, GLFW_KEY_2) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    if (glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS)
        camera->ProcessKeyboard(FORWARD, deltaTime * 10);
    if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS)
        camera->ProcessKeyboard(BACKWARD, deltaTime * 10);
    if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS)
        camera->ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS)
        camera->ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(this->window, GLFW_KEY_Q) == GLFW_PRESS)
        camera->ProcessKeyboard(UP, deltaTime);
    if (glfwGetKey(this->window, GLFW_KEY_E) == GLFW_PRESS)
        camera->ProcessKeyboard(DOWN, deltaTime);
    if (glfwGetKey(this->window, GLFW_KEY_0) == GLFW_PRESS)
        drawterrain = !drawterrain;
    if (glfwGetKey(this->window, GLFW_KEY_9) == GLFW_PRESS)
        drawsky = !drawsky;
    if (glfwGetKey(this->window, GLFW_KEY_8) == GLFW_PRESS)
        drawwater = !drawwater;
    if (glfwGetKey(this->window, GLFW_KEY_7) == GLFW_PRESS)
        drawreflect = !drawreflect;

    newState = glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_RIGHT);

    if (newState == GLFW_RELEASE && oldState == GLFW_PRESS) {
        glfwSetInputMode(this->window, GLFW_CURSOR, (mouseCursorDisabled
            ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL));
        mouseCursorDisabled = !mouseCursorDisabled;
        if (mouseCursorDisabled)
            firstMouse = true;
        //std::cout << "MOUSE R PRESSED!" << std::endl;
    }
    oldState = newState;

}

Window::~Window() {
    this->terminate();

}