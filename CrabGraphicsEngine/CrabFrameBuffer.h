#ifndef CrabEngine_Graphics_FrameBuffer_HEADER
#define CrabEngine_Graphics_FrameBuffer_HEADER

#include "GLEW/glew.h"

namespace CrabEngine {
    namespace Graphics {

        typedef class Window Window;
        typedef class Texture Texture;

        class FrameBuffer {
        public:

            FrameBuffer(Window* window);
            ~FrameBuffer();

            void Init(bool reset);

            void setTexture(Texture* tex);

            void resize(unsigned width, unsigned height);

            void bind();
            void unbind();

        private:

            Window* m_window;
            Texture* m_tex;

            GLuint m_fbo;
            GLuint m_rbo;

            unsigned m_width;
            unsigned m_height;

        };

    }
}

#endif
