
#ifndef CrabEngine_Graphics_Window_HEADER
#define CrabEngine_Graphics_Window_HEADER

#include <string>
#include <vector>

typedef struct GLFWwindow GLFWwindow;

namespace CrabEngine {
    namespace Graphics {

        struct windowInitEventCallback {
            void(*func)(void* context);
            void* context;
        };

        class Window {
        public:
            Window(unsigned width, unsigned height, std::string name, bool fullscreen, bool borderless, bool vSync, unsigned MSAA);
            ~Window();

            void registerInitFunc(const windowInitEventCallback& callback);
            void removeInitFunc(void* context);

            void update();

            int fbWidth();
            int fbHeight();

            double cursorX();
            double cursorY();

            GLFWwindow* glfwWindow();

            bool shouldClose();

            bool keyDown(int key);

            void setWidth(const unsigned &width);
            void setHeight(const unsigned &height);
            void setFullscreen(const bool &fullscreen);
            void setBorderless(const bool &borderless);
            void setVSync(const bool &vSync);
            void setMSAA(const unsigned &MSAAlevel);
            void setName(const std::string name);

            void initialize();

        private:
            int m_fbWidth, m_fbHeight;
            unsigned m_width, m_height, m_MSAA;
            bool m_fullscreen, m_borderless, m_vSync;
            double m_cursorX, m_cursorY;

            std::string m_name;

            GLFWwindow* m_window;

            //array of intiailize functions
            std::vector<windowInitEventCallback> m_initFuncs;

        };
    }
}


#endif
