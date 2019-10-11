#include "CrabIBO.h"

namespace CrabEngine {
    namespace Graphics {
        IBO::IBO(const GLuint* data, GLuint count) : m_count(count) {
            glGenBuffers(1, &m_ibo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(GLuint), data, GL_STATIC_DRAW);
        }
        IBO::~IBO() {
            glDeleteBuffers(1, &m_ibo);
        }

        void IBO::bind() {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
        }
        void IBO::unbind() {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

        GLuint IBO::getCount() {
            return m_count;
        }
    }
}
