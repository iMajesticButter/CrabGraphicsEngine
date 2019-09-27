
#ifndef CrabEngine_Graphics_Window_HEADER
#define CrabEngine_Graphics_Window_HEADER

typedef struct GLFWwindow GLFWwindow;

namespace CrabEngine {
    namespace Graphics {

        class Window {
        public:
            Window(unsigned width, unsigned height, bool fullscreen, bool borderless, bool vSync, unsigned MSAA);
            ~Window();

            void updateFrameBufferSize();

            int fbWidth();
            int fbHeight();

            GLFWwindow* glfwWindow();

            bool shouldClose();

            void setWidth(const unsigned &width);
            void setHeight(const unsigned &height);
            void setFullscreen(const bool &fullscreen);
            void setBorderless(const bool &borderless);
            void setVSync(const bool &vSync);
            void setMSAA(const unsigned &MSAAlevel);

            void initialize();

        private:
            int m_fbWidth, m_fbHeight;
            unsigned m_width, m_height, m_MSAA;
            bool m_fullscreen, m_borderless, m_vSync;

            GLFWwindow* m_window;

        };
    }
}


#endif
