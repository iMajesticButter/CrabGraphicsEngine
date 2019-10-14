#ifndef CrabEngine_Graphics_Mesh_HEADER
#define CrabEngine_Graphics_Mesh_HEADER

#include "CrabVec2.h"
#include "CrabVec3.h"
#include "CrabVec4.h"
#include "CrabVBO.h"

#include <vector>
#include <cstring>

namespace CrabEngine {
    namespace Graphics {

        class Mesh {
        public:

            std::vector<CrabEngine::Math::Vec2> vertecies;
            std::vector<CrabEngine::Math::Vec2> uvCooordinates;

            std::vector<unsigned int> triangles;

            Mesh();

            std::vector<GLfloat> getVertexData();

            VBOlayout getLayout();

        private:

            VBOlayout m_layout;
            GLuint m_attributeSize;

        };

    }
}

#endif
