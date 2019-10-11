#ifndef CrabEngine_Graphics_VAO_HEADER
#define CrabEngine_Graphics_VAO_HEADER

#include "CrabVBO.h"
#include "CrabWindow.h"
#include <vector>

namespace CrabEngine {
    namespace Graphics {

        class VAO {
        public:
            VAO();
            ~VAO();

            void bind();
            void unbind();

            void draw(unsigned count);

        private:
            GLuint m_vao;
            Window* m_window;
        };

    }
}

#endif
