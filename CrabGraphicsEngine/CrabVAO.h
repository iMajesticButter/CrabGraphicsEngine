#ifndef CrabEngine_Graphics_VAO_HEADER
#define CrabEngine_Graphics_VAO_HEADER

#include "CrabVBO.h"
#include <vector>

namespace CrabEngine {
    namespace Graphics {

        class VAO {
        public:
            VAO();
            ~VAO();

            void pushBuffer(VBO* vbo);

            void bind();
            void unbind();

            void draw(unsigned count);
        private:
            std::vector<VBO*> m_vbos;
        };

    }
}

#endif
