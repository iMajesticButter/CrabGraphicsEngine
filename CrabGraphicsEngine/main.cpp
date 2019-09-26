#include <glew.h>
#include <glfw3.h>
#include <iostream>


void glfwErrorCallback(int err, const char* description) {
    std::cerr << "ERROR: " << description << std::endl;
}


int main() {

    if(!glfwInit()) {
        std::cerr << "FAILED TO INITIALIZE GLFW!" << std::endl;
    }


    glfwSetErrorCallback(glfwErrorCallback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    GLFWwindow* window = glfwCreateWindow(300, 300, "TEST", nullptr, nullptr);

    if(!window) {
        std::cerr << "WINDOW CONTEXT CREATION FAILED!" << std::endl;
    }

    glfwDestroyWindow(window);

    glfwTerminate();

    return 0;
}
