#include "CrabIBO.h"

namespace CrabEngine {
    namespace Graphics {
        IBO::IBO(VBOusage usage) {
            glGenBuffers(1, &m_ibo);
            m_usage = usage == STATIC ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW;
        }
        IBO::~IBO() {
            glDeleteBuffers(1, &m_ibo);
        }

        void IBO::setData(const unsigned count, const void* data) {
            m_count = count;
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_count*sizeof(GLuint), data, m_usage);
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
