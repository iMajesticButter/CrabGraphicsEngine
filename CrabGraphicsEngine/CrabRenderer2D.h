#ifndef CrabEngine_Graphics_Renderer2D_HEADER
#define CrabEngine_Graphics_Renderer2D_HEADER

#include "GLEW/glew.h"
#include "CrabWindow.h"
#include "CrabMaterial.h"
#include "CrabVec4.h"
#include "CrabFrameBuffer.h"
#include "CrabTexture.h"

#include <vector>
#include <chrono>

#define byte unsigned char

namespace CrabEngine {
    namespace Graphics {

        typedef class VAO VAO;
        typedef class VBO VBO;
        typedef class IBO IBO;
        typedef class GraphicsObject2D GraphicsObject2D;
        typedef class Camera Camera;
        typedef class Texture Texture;


        class Renderer2D {
        public:

            Renderer2D(Window* window);
            ~Renderer2D();

            void Init();

            void drawScreenSpaceTexture(Texture* tex, float x = 0.0f, float y = 0.0f, float width = 1.0f, float height = 1.0f, float alpha = 1.0f);
            void drawScreenSpaceTexture(Texture* tex, CrabEngine::Math::Vec4 viewport, float alpha = 1.0f);

            void start();
            void pushCamera(Camera* cam);
            void pushObject(GraphicsObject2D* obj);
            void end();

        private:

            void drawPostEffectQuad(Texture* tex, Material* mat);

            Window* m_window;

            std::vector<GraphicsObject2D*> m_objects;
            std::vector<Camera*> m_cams;

            VAO* m_vao = nullptr;
            VBO* m_vbo = nullptr;
            IBO* m_ibo = nullptr;

            VAO* m_vaoQuad = nullptr;
            VBO* m_vboQuad = nullptr;
            IBO* m_iboQuad = nullptr;

            bool m_active = false;

            unsigned m_numVertecies;
            unsigned m_numIndecies;

            Material m_screenSpaceImageMat;
            FragmentShader m_screenSpaceImageFrag;
            VertexShader m_screenSpaceImageVert;

            FrameBuffer m_fbo;
            Texture m_tex0;
            Texture m_tex1;

            float m_time;
            std::chrono::time_point<std::chrono::steady_clock> m_startTime;

        };
    }
}

#endif
