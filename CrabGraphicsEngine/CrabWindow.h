
#ifndef CrabEngine_Graphics_Window_HEADER
#define CrabEngine_Graphics_Window_HEADER

#include <string>
#include <vector>
#include "CrabVec2.h"

typedef struct GLFWwindow GLFWwindow;

namespace CrabEngine {
    namespace Graphics {

        struct windowInitEventCallback {
            void(*func)(void* context);
            void* context;
        };

        class Window {
        public:
            Window(int width, int height, std::string name, bool fullscreen, bool borderless, bool resizeable, bool vSync, unsigned MSAA);
            Window(CrabEngine::Math::Vec2 resolution, std::string name, bool fullscreen, bool borderless, bool resizeable, bool vSync, unsigned MSAA);
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

            CrabEngine::Math::Vec2 getMonitorResolution() const;

            void setWidth(const unsigned& width);
            void setHeight(const unsigned& height);
            void setFullscreen(const bool& fullscreen);
            void setBorderless(const bool& borderless);
            void setVSync(const bool& vSync);
            void setMSAA(const unsigned& MSAAlevel);
            void setName(const std::string name);
            void setResizeable(const bool& resizeable);

            void initialize();

        private:
            void construct(int width, int height, std::string name, bool fullscreen, bool borderless, bool resizeable, bool vSync, unsigned MSAA);

            int m_fbWidth, m_fbHeight;
            unsigned m_width, m_height, m_MSAA;
            bool m_fullscreen, m_borderless, m_vSync, m_resizeable;
            double m_cursorX, m_cursorY;

            std::string m_name;

            GLFWwindow* m_window;

            //array of intiailize functions
            std::vector<windowInitEventCallback> m_initFuncs;

        };
    }
}


#endif
