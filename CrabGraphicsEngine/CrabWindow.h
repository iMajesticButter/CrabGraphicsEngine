
#ifndef CrabEngine_Graphics_Window_HEADER
#define CrabEngine_Graphics_Window_HEADER

typedef struct GLFWwindow GLFWwindow;

namespace CrabEngine {
    namespace Graphics {

        class Window {
        public:
            Window(int width, int height, unsigned MSAA);
            ~Window();

            void updateWindowSize();

            int width();
            int height();

            GLFWwindow* glfwWindow();

            bool shouldClose();

        private:
            int m_width, m_height;

            GLFWwindow* m_window;

        };
    }
}


#endif
