#include "GLEW/glew.h"

#include "CrabDebugRenderer.h"
#include "CrabShader.h"

#define _USE_MATH_DEFINES
#include <math.h>


namespace CrabEngine {
    namespace Graphics {

        void DebugRendererInitCallback(void* context) {
            ((DebugRenderer*)context)->Init();
        }


        DebugRenderer::DebugRenderer(Window* window) : m_vbo(nullptr), m_vao(nullptr), m_vboCircle(nullptr), m_vaoCircle(nullptr), m_debugMat(*window, "material for debug stuff"), m_window(window) {
            windowInitEventCallback callback;
            callback.context = this;
            callback.func = DebugRendererInitCallback;
            m_window->registerInitFunc(callback);

            m_debugMat.AddShader(VertexShader("internalShaders/Debug.vs"));
            m_debugMat.AddShader(FragmentShader("internalShaders/Debug.fs"));
            m_debugMat.Initialize();

            Init();
        }
        DebugRenderer::~DebugRenderer() {
            m_window->removeInitFunc(this);
        }

        void DebugRenderer::Init() {
            if(m_vbo != nullptr)
                delete m_vbo;

            if(m_vao != nullptr)
                delete m_vao;

            m_vao = new VAO();
            m_vao->bind();
            m_vbo = new VBO(VBOusage::DYNAMIC);
            m_vbo->bind();

            //set vbo layout
            VBOlayout layout;
            layout.addAttribute(GL_FLOAT, 3, sizeof(GLfloat));

            m_vbo->setLayout(layout);

            m_vao->unbind();

            if(m_vboCircle != nullptr)
                delete m_vboCircle;

            if(m_vaoCircle != nullptr)
                delete m_vaoCircle;

            m_vaoCircle = new VAO();
            m_vaoCircle->bind();
            m_vboCircle = new VBO(VBOusage::STATIC);
            m_vboCircle->bind();

            m_vboCircle->setLayout(layout);

            using namespace CrabEngine::Math;

            //set circle vbo data
            float circleData[3*360];
            for(unsigned i = 0; i < 360; ++i) {
                float radians = (i/180.0f)*M_PI;
                Vec3 vert(cos(radians), sin(radians), 0);
                circleData[(i*3)  ] = vert.x;
                circleData[(i*3)+1] = vert.y;
                circleData[(i*3)+2] = vert.z;
            }

            m_vboCircle->setData(sizeof(GLfloat)*(3*360), circleData);

            m_vaoCircle->unbind();

        }

        void DebugRenderer::AddLine(const CrabEngine::Math::Vec3& start, const CrabEngine::Math::Vec3& end, const CrabEngine::Math::Vec3& color) {
            m_lines.emplace_back(std::tuple<CrabEngine::Math::Vec3, CrabEngine::Math::Vec3, CrabEngine::Math::Vec3>(start, end, color));
        }
        void DebugRenderer::AddCircle(const CrabEngine::Math::Vec3& center, float radius, const CrabEngine::Math::Vec3& color) {
            m_circles.emplace_back(std::tuple<CrabEngine::Math::Vec3, float, CrabEngine::Math::Vec3>(center, radius, color));
        }
        void DebugRenderer::Draw(const CrabEngine::Math::Mat4& projection, const CrabEngine::Math::Mat4& view) {
            glLineWidth(3);

            m_vao->bind();

            m_debugMat.bind();
            m_debugMat.setUniformMat4("MVP", projection * view);

            GLfloat data[6];

            for(unsigned i = 0; i < m_lines.size(); ++i) {

                data[0] = std::get<0>(m_lines[i]).x;
                data[1] = std::get<0>(m_lines[i]).y;
                data[2] = std::get<0>(m_lines[i]).z;

                data[3] = std::get<1>(m_lines[i]).x;
                data[4] = std::get<1>(m_lines[i]).y;
                data[5] = std::get<1>(m_lines[i]).z;

                m_vbo->setData(sizeof(GLfloat) * 6, data);
                m_debugMat.setUniform3f("Color", std::get<2>(m_lines[i]));

                glDrawArrays(GL_LINES, 0, 2);

            }
            m_debugMat.unbind();
            m_vao->unbind();

            m_vaoCircle->bind();
            m_debugMat.bind();

            using namespace CrabEngine::Math;

            for(unsigned i = 0; i < m_circles.size(); ++i) {

                Vec3 pos = std::get<0>(m_circles[i]);
                float radius = std::get<1>(m_circles[i]);

                m_debugMat.setUniform3f("Color", std::get<2>(m_circles[i]));

                TranslationMatrix transMat(pos);
                ScaleMatrix scaleMat(Vec2(radius, radius));
                Mat4 MVP(projection * view * scaleMat * transMat);

                m_debugMat.setUniformMat4("MVP", MVP);

                glDrawArrays(GL_LINE_LOOP, 0, 360);

            }

            m_debugMat.unbind();
            m_vaoCircle->unbind();

            glLineWidth(1);
        }
        void DebugRenderer::Clear() {
            m_lines.clear();
            m_circles.clear();
        }
    }
}
