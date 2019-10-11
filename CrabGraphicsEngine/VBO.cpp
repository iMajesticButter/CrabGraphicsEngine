#include "CrabVBO.h"

namespace CrabEngine {
    namespace Graphics {

        //---------------------------------
        // VBO layout
        //---------------------------------

        VBOlayout::VBOlayout() : m_stride(0), m_index(0), m_count(0) {
            m_attributes = std::vector<VBOattribute>();
        }
        VBOlayout::VBOlayout(const VBOlayout& other) : m_stride(other.m_stride), m_index(other.m_index), m_count(other.m_count) {
            m_attributes = other.m_attributes;
        }
        VBOlayout::VBOlayout(GLuint stride) : m_stride(stride), m_index(0), m_count(0) {
            m_attributes = std::vector<VBOattribute>();
        }

        void VBOlayout::addAttribute(std::string name, GLenum type, GLuint count, GLuint size, GLboolean normalized) {
            VBOattribute attr;
            attr.type = type;
            attr.count = count;
            attr.normalized = normalized;
            attr.offset = m_count;
            attr.location = m_index;
            attr.name = name;
            m_count += size;
            ++m_index;
            m_attributes.push_back(attr);
        }
        void VBOlayout::clearAttributes() {
            m_attributes.clear();
            m_count = 0;
            m_index = 0;
        }

        //---------------------------------
        // VBO
        //---------------------------------

        VBO::VBO(VBOusage usage) : m_usage(usage) {
            glCreateBuffers(1, &m_vbo);
        }
        VBO::~VBO() {
            glDeleteBuffers(1, &m_vbo);
        }

        void VBO::resize(unsigned size) {
            m_size = size;

            glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
            glBufferData(GL_ARRAY_BUFFER, size, NULL, m_usage == VBOusage::DYNAMIC ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
        }
        void VBO::setLayout(const VBOlayout& layout) {
            m_layout = layout;
            for(unsigned i = 0; i < layout.m_attributes.size(); ++i) {
                const VBOattribute& attr = layout.m_attributes[i];
                glEnableVertexAttribArray(i);
                glVertexAttribPointer(i, attr.count, attr.type, attr.normalized, layout.m_stride, (GLvoid*)attr.offset);
            }
        }
        void VBO::setData(const unsigned size, const void* data) {
            glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
            glBufferData(GL_ARRAY_BUFFER, size, data, m_usage == VBOusage::DYNAMIC ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
        }
        void* VBO::getPointerInternal() {
            return glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
        }
        void VBO::releasePointer() {
            glUnmapBuffer(GL_ARRAY_BUFFER);
        }
        void VBO::bind() {
            setLayout(m_layout);
            glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        }
        void VBO::unbind() {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
    }
}
