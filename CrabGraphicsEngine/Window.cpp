#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <algorithm>

#include "CrabWindow.h"

void glfwErrorCallback(int err, const char* description) {
    std::cerr << "ERROR: " << err << " (" << description << ")" << std::endl;
}

namespace CrabEngine {
    namespace Graphics {

        //-------------------
        // Public Functions
        //-------------------

        Window::Window(int width, int height, std::string name, bool fullscreen, bool borderless, bool resizeable, bool vSync, unsigned MSAA) :
        m_window(nullptr) {
            construct(width, height, name, fullscreen, borderless, resizeable, vSync, MSAA);
        }

        Window::Window(CrabEngine::Math::Vec2 resolution, std::string name, bool fullscreen, bool borderless, bool resizeable, bool vSync, unsigned MSAA) :
        m_window(nullptr) {
            construct(resolution.x, resolution.y, name, fullscreen, borderless, resizeable, vSync, MSAA);
        }

        Window::~Window() {
            if(m_window != nullptr) {
                glfwDestroyWindow(m_window);
            }
            glfwTerminate();
        }

        void Window::registerInitFunc(windowInitEventCallback& Callback) {
            m_initFuncs.push_back(Callback);
        }

        void Window::removeInitFunc(void* context) {
            for(unsigned i = 0; i < m_initFuncs.size(); ++i) {
                if(m_initFuncs[i].context == context) {
                    m_initFuncs.erase(m_initFuncs.begin() + i);
                }
            }
        }

        void Window::update() {
            glfwSwapBuffers(m_window);

            glfwGetFramebufferSize(m_window, &m_fbWidth, &m_fbHeight);
            glfwPollEvents();
            glfwGetCursorPos(m_window, &m_cursorX, &m_cursorY);
        }

        int Window::fbWidth() {
            return m_fbWidth;
        }
        int Window::fbHeight() {
            return m_fbHeight;
        }

        double Window::cursorX() {
            return m_cursorX;
        }
        double Window::cursorY() {
            return m_cursorY;
        }

        GLFWwindow* Window::glfwWindow() {
            return m_window;
        }

        bool Window::shouldClose() {
            return glfwWindowShouldClose(m_window);
        }

        bool Window::keyDown(int key) {
            return glfwGetKey(m_window, key);
        }

        CrabEngine::Math::Vec2 Window::getMonitorResolution() const {
            CrabEngine::Math::Vec2 res;

            const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

            res.x = mode->width;
            res.y = mode->height;

            return res;
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
            if(m_window != nullptr) {
                if(m_vSync) {
                    //enable vSync
                    glfwSwapInterval(1);
                } else {
                    //disable vSync
                    glfwSwapInterval(0);
                }
            }
        }
        void Window::setMSAA(const unsigned &MSAAlevel) {
            m_MSAA = MSAAlevel;
        }
        void Window::setName(const std::string name) {
            m_name = name;
        }
        void Window::setResizeable(const bool& resizeable) {
            m_resizeable = resizeable;
        }

        void Window::initialize() {

            //if window already exists, destroy it and replace it with the new one
            if(m_window != nullptr) {
                glfwDestroyWindow(m_window);
            }

            //get monitor
            //GLFWmonitor* monitor = glfwGetPrimaryMonitor();
            int count;
            GLFWmonitor* monitor = glfwGetMonitors(&count)[0];

            //set MSAA
            glfwWindowHint(GLFW_SAMPLES, m_MSAA);

            if(!m_fullscreen) {
                monitor = nullptr;
            }

            if(m_fullscreen && m_borderless) {
                //borderless fullscrenn (set window to montior video mode)
                const GLFWvidmode* mode = glfwGetVideoMode(monitor);

                glfwWindowHint(GLFW_RED_BITS, mode->redBits);
                glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
                glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
                glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

                //disable auto minimize
                glfwWindowHint(GLFW_AUTO_ICONIFY, false);
            } else if(m_fullscreen) {
                //enable auto minimize
                glfwWindowHint(GLFW_AUTO_ICONIFY, true);
            }

            glfwWindowHint(GLFW_DECORATED, !m_borderless);

            glfwWindowHint(GLFW_RESIZABLE, m_resizeable);

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

            GLFWwindow* newWindow = glfwCreateWindow(m_width, m_height, m_name.c_str(), monitor, nullptr);

            if(!newWindow) {
                glfwTerminate();
                std::cerr << "WINDOW CONTEXT CREATION FAILED!" << std::endl;
                throw std::runtime_error("WINDOW CONTEXT CREATION FAILED!");
                return;
            }

            m_window = newWindow;

            glfwMakeContextCurrent(m_window);
            glewInit();

            //run intitialize callbacks
            for(unsigned i = 0; i < m_initFuncs.size(); ++i) {
                m_initFuncs[i].func(m_initFuncs[i].context);
            }

            if(m_vSync) {
                //enable vSync
                glfwSwapInterval(1);
            } else {
                //disable vSync
                glfwSwapInterval(0);
            }

            //set key input mode
            glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GLFW_TRUE);

            update();
        }

        void Window::construct(int width, int height, std::string name, bool fullscreen, bool borderless, bool resizeable, bool vSync, unsigned MSAA) {
            //initialize glfw
            if(!glfwInit()) {
                std::cerr << "FAILED TO INITIALIZE GLFW!" << std::endl;
                throw std::runtime_error("FAILED TO INITIALIZE GLFW!");
                return;
            }

            if(width < 1 || height < 1) {
                const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

                width = width < 1 ? mode->width : width;
                height = height < 1 ? mode->height : height;

            }

            //set window settings
            setWidth((unsigned)width);
            setHeight((unsigned)height);
            setFullscreen(fullscreen);
            setBorderless(borderless);
            setVSync(vSync);
            setMSAA(MSAA);
            setName(name);
            setResizeable(resizeable);

            //set error callback
            glfwSetErrorCallback(glfwErrorCallback);
            //create window
            initialize();
        }
    }
}
