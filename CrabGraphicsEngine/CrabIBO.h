#ifndef CrabEngine_Graphics_IBO_HEADER
#define CrabEngine_Graphics_IBO_HEADER

#include <GLEW/glew.h>
#include "CrabWindow.h"
#include "CrabVBO.h"

namespace CrabEngine {
    namespace Graphics {

        class IBO {
        public:
            IBO(VBOusage usage);
            ~IBO();

            void setData(const unsigned size, const void* data);

            void bind();
            void unbind();

            GLuint getCount();

        private:
            GLuint m_ibo;
            GLuint m_count;
            Window* m_window;
            GLenum m_usage;
        };

    }
}

#endif
