#ifndef CrabEngine_Graphics_DebugRenderer_HEADER
#define CrabEngine_Graphics_DebugRenderer_HEADER


#include "CrabWindow.h"
#include "CrabVec3.h"
#include "CrabVBO.h"
#include "CrabVAO.h"
#include "CrabMaterial.h"

#include <tuple>
#include <vector>


namespace CrabEngine {
    namespace Graphics {

        class DebugRenderer {
        public:

            DebugRenderer(Window* window);
            ~DebugRenderer();

            void AddLine(const CrabEngine::Math::Vec3& start, const CrabEngine::Math::Vec3& end, const CrabEngine::Math::Vec3& color);
            void AddCircle(const CrabEngine::Math::Vec3& center, float radius, const CrabEngine::Math::Vec3& color);
            void Draw(const CrabEngine::Math::Mat4& projection, const CrabEngine::Math::Mat4& view);
            void Clear();

            friend void DebugRendererInitCallback(void* context);
        private:

            void Init();

            std::vector<std::tuple<CrabEngine::Math::Vec3, CrabEngine::Math::Vec3, CrabEngine::Math::Vec3>> m_lines;
            std::vector<std::tuple<CrabEngine::Math::Vec3, float, CrabEngine::Math::Vec3>> m_circles;

            VBO* m_vbo;
            VAO* m_vao;

            VBO* m_vboCircle;
            VAO* m_vaoCircle;

            Material m_debugMat;

            Window* m_window;

        };

    }
}

#endif
