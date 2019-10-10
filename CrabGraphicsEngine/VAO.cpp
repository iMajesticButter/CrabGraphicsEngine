#include "CrabVAO.h"

namespace CrabEngine {
    namespace Graphics {

        VAO::VAO() {
        }
        VAO::~VAO() {
        }

        void VAO::pushBuffer(VBO* vbo) {
            m_vbos.push_back(vbo);
        }

        void VAO::bind() {
            m_vbos.front()->bind();
        }
        void VAO::unbind() {
            m_vbos.front()->unbind();
        }

        void VAO::draw(unsigned count) {
            glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, NULL);
        }

    }
}
