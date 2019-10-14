#include "CrabMesh.h"

namespace CrabEngine {
    namespace Graphics {
        Mesh::Mesh() {
            m_layout.clearAttributes();
            m_layout.addAttribute(GL_FLOAT, 2, sizeof(GLfloat));
            m_layout.addAttribute(GL_FLOAT, 2, sizeof(GLfloat));
        }

        std::vector<GLfloat> Mesh::getVertexData() {

            uvCooordinates.resize(vertecies.size());

            std::vector<GLfloat> data;

            for(unsigned i = 0; i < vertecies.size(); ++i) {
                data.push_back(vertecies[i].x);
                data.push_back(vertecies[i].y);
                data.push_back(uvCooordinates[i].x);
                data.push_back(uvCooordinates[i].y);
            }

            return data;
        }

        VBOlayout Mesh::getLayout() {
            return m_layout;
        }
    }
}
