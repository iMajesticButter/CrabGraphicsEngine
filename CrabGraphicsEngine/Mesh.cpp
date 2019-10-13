#include "CrabMesh.h"

namespace CrabEngine {
    namespace Graphics {
        Mesh::Mesh() {
            m_layout.addAttribute(GL_FLOAT, 2, sizeof(GLfloat));
            m_layout.addAttribute(GL_FLOAT, 3, sizeof(GLfloat));
            m_layout.addAttribute(GL_FLOAT, 2, sizeof(GLfloat));
        }

        std::vector<unsigned char> Mesh::getVertexData() {

            colors.resize(vertecies.size());
            uvCooordinates.resize(vertecies.size());

            using namespace CrabEngine::Math;
            std::vector<unsigned char> data;
            unsigned vertSize = (sizeof(Vec2)*2) + sizeof(Vec3) + m_attributeSize;
            data.resize(vertSize * vertecies.size());
            for(unsigned i = 0; i < vertecies.size(); ++i) {
                memcpy(&data[i*vertSize], &vertecies[i], sizeof(Vec2));
                memcpy(&data[i*vertSize]+sizeof(Vec2), &colors[i], sizeof(Vec3));
                memcpy(&data[i*vertSize]+sizeof(Vec2) + sizeof(Vec3), &uvCooordinates[i], sizeof(Vec2));
            }
            return data;
        }

        VBOlayout Mesh::getLayout() {
            return m_layout;
        }
    }
}
