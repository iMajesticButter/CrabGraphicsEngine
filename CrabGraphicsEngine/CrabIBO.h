#ifndef CrabEngine_Graphics_IBO_HEADER
#define CrabEngine_Graphics_IBO_HEADER

#include <GLEW/glew.h>
#include "CrabWindow.h"

namespace CrabEngine {
    namespace Graphics {

        class IBO {
        public:
            IBO(const GLuint* data, GLuint count);
            ~IBO();

            void bind();
            void unbind();

            GLuint getCount();

        private:
            GLuint m_ibo;
            GLuint m_count;
            Window* m_window;
        };

    }
}

#endif
