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

            unsigned size = vertecies.size();

            std::vector<GLfloat> data;
            data.resize(size * 4, 0);

            for(unsigned i = 0; i < size; ++i) {
                /*data.push_back(vertecies[i].x);
                data.push_back(vertecies[i].y);
                data.push_back(uvCooordinates[i].x);
                data.push_back(uvCooordinates[i].y);*/
                unsigned offset = i*4;
                data[offset + 0] = vertecies[i].x;
                data[offset + 1] = vertecies[i].y;
                data[offset + 2] = uvCooordinates[i].x;
                data[offset + 3] = uvCooordinates[i].y;
            }

            return data;
        }

        void Mesh::copyVertexDataToPointer(float*& start) {

            uvCooordinates.resize(vertecies.size());

            unsigned size = vertecies.size();

            for(unsigned i = 0; i < size; ++i) {
                *(start    ) = vertecies[i].x;
                *(start + 1) = vertecies[i].y;
                *(start + 2) = uvCooordinates[i].x;
                *(start + 3) = uvCooordinates[i].y;
                start += 4;
            }

        }

        void Mesh::copyIndexDataToPointer(unsigned*& start, unsigned& offset) {

            unsigned size = triangles.size();

            for(unsigned i = 0; i < size; ++i) {
                *(start) = triangles[i] + offset;
                ++start;
            }
            offset += vertecies.size();

        }

        void Mesh::calculateBoundingBox() {
            using namespace CrabEngine::Math;
            boundingBox = Vec4(0);
            for(unsigned i = 0; i < vertecies.size(); ++i) {
                if(vertecies[i].x < boundingBox.x)
                    boundingBox.x = vertecies[i].x;
                if(vertecies[i].y < boundingBox.y)
                    boundingBox.y = vertecies[i].y;
                if(vertecies[i].x > boundingBox.z)
                    boundingBox.z = vertecies[i].x;
                if(vertecies[i].y > boundingBox.w)
                    boundingBox.w = vertecies[i].y;
            }
        }

        VBOlayout Mesh::getLayout() {
            return m_layout;
        }
    }
}
