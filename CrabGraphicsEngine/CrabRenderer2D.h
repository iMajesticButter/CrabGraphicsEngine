#ifndef CrabEngine_Graphics_Renderer2D_HEADER
#define CrabEngine_Graphics_Renderer2D_HEADER

#include "GLEW/glew.h"
#include "CrabWindow.h"
#include "CrabMaterial.h"
#include "CrabVec3.h"
#include "CrabVec4.h"
#include "CrabFrameBuffer.h"
#include "CrabTexture.h"
#include "CrabLight.h"

#include <vector>
#include <chrono>
#include <math.h>

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

            CrabEngine::Math::Vec3 ambientLight;

            Renderer2D(Window* window, CrabEngine::Math::Vec3 ambientLight = CrabEngine::Math::Vec3(1,1,1));
            ~Renderer2D();

            void Init();

            void drawScreenSpaceTexture(Texture* tex, float x = 0.0f, float y = 0.0f, float width = 1.0f, float height = 1.0f, float alpha = 1.0f);
            void drawScreenSpaceTexture(Texture* tex, CrabEngine::Math::Vec4 viewport, float alpha = 1.0f, unsigned fbWidth = 0, unsigned fbHeight = 0);

            void start();
            void pushCamera(Camera* cam);
            void pushObject(GraphicsObject2D* obj);
            void pushLight(Light* light);
            void end(Texture* outputTexture = nullptr);

        private:

            void drawPostEffectQuad(Texture* tex, Material* mat);

            Window* m_window;

            std::vector<GraphicsObject2D*> m_objects;
            std::vector<Light*> m_lights;
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

            unsigned m_numVerteciesShadowCasters;
            unsigned m_numIndeciesShadowCasters;

            Material m_screenSpaceImageMat;
            FragmentShader m_screenSpaceImageFrag;
            VertexShader m_screenSpaceImageVert;

            Texture m_tex0;
            Texture m_tex1;
            Texture m_ditherPattern;
            FrameBuffer m_fbo;
            FrameBuffer m_fbo0;
            FrameBuffer m_fbo1;

            Texture m_shadowCasterTex;
            FrameBuffer m_shadowCasterFBO;
            Texture m_shadowMapTex;
            FrameBuffer m_shadowMapFBO;
            Texture m_lightsTex;
            FrameBuffer m_lightFBO;

            FragmentShader m_shadowMapFrag;
            VertexShader m_shadowMapVert;
            Material m_shadowMapMat;
            FragmentShader m_lightFrag;
            VertexShader m_lightVert;
            Material m_lightMat;

            float m_time;
            std::chrono::time_point<std::chrono::steady_clock> m_startTime;

        };
    }
}

#endif
