#include "CrabWindow.h"
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

void glfwErrorCallback(int err, const char* description) {
    std::cerr << "ERROR: " << description << std::endl;
}

namespace CrabEngine {
    namespace Graphics {

        //-------------------
        // Public Functions
        //-------------------

        Window::Window(unsigned width, unsigned height, bool fullscreen, bool borderless, bool vSync, unsigned MSAA) {
            //set window settings

            setWidth(width);
            setHeight(height);
            setFullscreen(fullscreen);
            setBorderless(borderless);
            setVSync(vSync);
            setMSAA(MSAA);

            //initialize glfw
            glfwInit();
            glfwSetErrorCallback(glfwErrorCallback);

            //create window
            initialize();
        }
        Window::~Window() {
            glfwDestroyWindow(m_window);
            glfwTerminate();
        }

        void Window::updateFrameBufferSize() {
            glfwGetFramebufferSize(m_window, &m_fbWidth, &m_fbHeight);
        }

        int Window::fbWidth() {
            return m_fbWidth;
        }
        int Window::fbHeight() {
            return m_fbHeight;
        }

        GLFWwindow* Window::glfwWindow() {
            return m_window;
        }

        bool Window::shouldClose() {
            return glfwWindowShouldClose(m_window);
        }

        void Window::setWidth(const unsigned &width) {
            m_width = width;
        }
        void Window::setHeight(const unsigned &height) {
            m_height = height;
        }
        void Window::setFullscreen(const bool &fullscreen) {
            m_fullscreen = fullscreen;
        }
        void Window::setBorderless(const bool &borderless) {
            m_borderless = borderless;
        }
        void Window::setVSync(const bool &vSync) {
            m_vSync = vSync;
        }
        void Window::setMSAA(const unsigned &MSAAlevel) {
            m_MSAA = MSAAlevel;
        }

        void Window::initialize() {

            //TODO: create window using settings and replace old one (if any), than call glewInit()

        }

    }
}
