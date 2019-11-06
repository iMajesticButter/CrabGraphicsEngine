#include "GLEW/glew.h"

#include "CrabDebugRenderer.h"
#include "CrabShader.h"


namespace CrabEngine {
    namespace Graphics {

        void DebugRendererInitCallback(void* context) {
            ((DebugRenderer*)context)->Init();
        }


        DebugRenderer::DebugRenderer(Window* window) : m_vbo(nullptr), m_vao(nullptr), m_debugMat(*window, "material for debug stuff"), m_window(window) {
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

        }

        void DebugRenderer::AddLine(const CrabEngine::Math::Vec3& start, const CrabEngine::Math::Vec3& end, const CrabEngine::Math::Vec3& color) {
            m_lines.emplace_back(std::tuple<CrabEngine::Math::Vec3, CrabEngine::Math::Vec3, CrabEngine::Math::Vec3>(start, end, color));
        }
        void DebugRenderer::Draw(const CrabEngine::Math::Mat4& projection, const CrabEngine::Math::Mat4& view) {
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

                glDrawBuffer(GL_LINES);

            }

            m_debugMat.unbind();
            m_vao->unbind();
        }
        void DebugRenderer::Clear() {
            m_lines.clear();
        }
    }
}
