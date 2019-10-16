#include "CrabVAO.h"

namespace CrabEngine {
    namespace Graphics {

        VAO::VAO() {
            glGenVertexArrays(1, &m_vao);
        }
        VAO::~VAO() {
            glDeleteVertexArrays(1, &m_vao);
        }

        void VAO::bind() {
            glBindVertexArray(m_vao);
        }
        void VAO::unbind() {
            glBindVertexArray(0);
        }

        void VAO::draw(unsigned count, unsigned offset) {
            glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, (void*)offset);
        }
    }
}
