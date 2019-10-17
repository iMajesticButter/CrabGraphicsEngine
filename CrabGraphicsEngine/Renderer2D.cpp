//#include "GLEW/glew.h"

#include "CrabRenderer2D.h"
#include "CrabGraphicsObject2D.h"
#include "CrabCamera.h"
#include "CrabVAO.h"
#include "CrabVBO.h"
#include "CrabIBO.h"
#include "CrabMat4.h"
#include "CrabVec4.h"

#include <iostream>
#include <algorithm>
#include <cstring>

namespace CrabEngine{
    namespace Graphics{

        //-------------------------------------------------------
        // Local Funcs
        //-------------------------------------------------------

        void InitCallback(void* context) {
            ((Renderer2D*)context)->Init();
        }

        bool SortObjectsCallback(GraphicsObject2D* obj1, GraphicsObject2D* obj2) {
            return obj1->renderLayer < obj2->renderLayer;
        }

        bool SortCamsCallback(Camera* cam1, Camera* cam2) {
            return cam1->renderLayer < cam2->renderLayer;
        }

        //-------------------------------------------------------
        // Renderer 2D
        //-------------------------------------------------------

        Renderer2D::Renderer2D(Window* window) : m_window(window), m_screenSpaceImageMat(*window, "Screen Space Image"),
                m_screenSpaceImageFrag("./internalShaders/screenSpaceImage.fs"),
                m_screenSpaceImageVert("./internalShaders/screenSpaceImage.vs"),
                m_fbo(window),
                m_tex0(*window),
                m_tex1(*window) {
            windowInitEventCallback callback;
            callback.context = this;
            callback.func = InitCallback;
            m_window->registerInitFunc(callback);

            m_screenSpaceImageMat.AddShader(m_screenSpaceImageFrag);
            m_screenSpaceImageMat.AddShader(m_screenSpaceImageVert);
            m_screenSpaceImageMat.Initialize();

            m_tex0.setFilteringMode(LINEAR);
            m_tex1.setFilteringMode(LINEAR);

            Init();
        }
        Renderer2D::~Renderer2D() {
            m_window->removeInitFunc(this);

            if(m_vbo != nullptr)
                delete m_vbo;

            if(m_vao != nullptr)
                delete m_vao;

            if(m_ibo != nullptr)
                delete m_ibo;

            if(m_vboQuad != nullptr)
                delete m_vboQuad;

            if(m_vaoQuad != nullptr)
                delete m_vaoQuad;

            if(m_iboQuad != nullptr)
                delete m_iboQuad;
        }

        void Renderer2D::Init() {
            //delete invalid old stuff if it exists
            if(m_vbo != nullptr)
                delete m_vbo;

            if(m_vao != nullptr)
                delete m_vao;

            if(m_ibo != nullptr)
                delete m_ibo;

            //create vao vbo and ibo
            m_vao = new VAO();
            m_vao->bind();
            m_vbo = new VBO(VBOusage::DYNAMIC);
            m_vbo->bind();
            m_ibo = new IBO(VBOusage::DYNAMIC);

            //set vbo layout
            VBOlayout layout;
            layout.addAttribute(GL_FLOAT, 2, sizeof(GLfloat));
            layout.addAttribute(GL_FLOAT, 2, sizeof(GLfloat));

            m_vbo->setLayout(layout);

            m_vao->unbind();

            //create quad
            if(m_vboQuad != nullptr)
                delete m_vboQuad;

            if(m_vaoQuad != nullptr)
                delete m_vaoQuad;

            if(m_iboQuad != nullptr)
                delete m_iboQuad;

            //create quad vao vbo and ibo
            m_vaoQuad = new VAO();
            m_vaoQuad->bind();
            m_vboQuad = new VBO(VBOusage::STATIC);
            m_vboQuad->bind();
            m_iboQuad = new IBO(VBOusage::STATIC);

            //set quad vbo layout
            m_vboQuad->setLayout(layout);

            //set quad vertecies and indices
            const float quadVertecies[] {
              //  x      y               s     t
                 1.0f,  1.0f,           1.0f, 1.0f,
                 1.0f, -1.0f,           1.0f, 0.0f,
                -1.0f, -1.0f,           0.0f, 0.0f,
                -1.0f,  1.0f,           0.0f, 1.0f
            };
            const unsigned quadIndices[] {
                0, 1, 2,
                0, 3, 2
            };

            m_vboQuad->setData(sizeof(float) * 16, quadVertecies);
            m_iboQuad->setData(sizeof(unsigned) * 6, quadIndices);

            m_vaoQuad->unbind();

            //enable blending
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }


        void Renderer2D::drawScreenSpaceTexture(Texture* tex, float x, float y, float width, float height, float alpha) {
            drawScreenSpaceTexture(tex, CrabEngine::Math::Vec4(x,y,width,height), alpha);
        }
        void Renderer2D::drawScreenSpaceTexture(Texture* tex, CrabEngine::Math::Vec4 viewport, float alpha) {

            glViewport(0, 0, m_window->fbWidth(), m_window->fbHeight());

            m_screenSpaceImageMat.setUniform4f("viewport", viewport);
            m_screenSpaceImageMat.setUniform1f("alpha", alpha);

            tex->bind(0);

            m_screenSpaceImageMat.setUniform1i("tex", 0);

            m_vaoQuad->bind();
            m_iboQuad->bind();
            m_screenSpaceImageMat.bind();
            m_vaoQuad->draw(6);
            m_screenSpaceImageMat.unbind();
            m_iboQuad->unbind();
            m_vaoQuad->unbind();

        }


        void Renderer2D::start() {
            if(m_active) {
                std::cerr << "Renderer is already active!, call Renderer2D::end()" << std::endl;
                return;
            }

            m_active = true;
            m_objects.clear();
            m_cams.clear();

            m_numIndecies = 0;
            m_numVertecies = 0;
        }
        void Renderer2D::pushCamera(Camera* cam) {
            if(!m_active) {
                std::cerr << "Renderer is not active!, call Renderer2D::start()" << std::endl;
                return;
            }

            if(cam->active) {
                m_cams.push_back(cam);
            }

        }
        void Renderer2D::pushObject(GraphicsObject2D* obj) {
            if(!m_active) {
                std::cerr << "Renderer is not active!, call Renderer2D::start()" << std::endl;
                return;
            }

            if(obj->visible && obj->getMesh() != nullptr && obj->getMaterial() != nullptr) {
                m_objects.push_back(obj);

                m_numVertecies += obj->getMesh()->vertecies.size();
                m_numIndecies += obj->getMesh()->triangles.size();
            }

        }


        void Renderer2D::end() {
            if(!m_active) {
                std::cerr << "Renderer is not active!, call Renderer2D::start()" << std::endl;
                return;
            }
            m_active = false;

            //sort the objects and cams so they rander in the correct order
            std::sort(m_objects.begin(), m_objects.end(), SortObjectsCallback);
            std::sort(m_cams.begin(), m_cams.end(), SortCamsCallback);

            //do the actual rendering

            //build the vbo and ibo
            m_vao->bind();

            //set vbo and ibo data
            unsigned* iboData = new unsigned[m_numIndecies];
            unsigned* iboDataIterator = iboData;

            float* vboData = new float[m_numVertecies*4];
            float* vboDataIterator = vboData;

            std::vector<GLfloat> data;

            unsigned offset = 0;

            for(unsigned i = 0; i < m_objects.size(); ++i) {
                //copy data to vbo
                data = m_objects[i]->getMesh()->getVertexData();

                //copy data to ibo
                for(unsigned j = 0; j < m_objects[i]->getMesh()->triangles.size(); ++j) {
                    *(iboDataIterator + j) = m_objects[i]->getMesh()->triangles[j] + offset;
                }
                iboDataIterator += m_objects[i]->getMesh()->triangles.size();
                offset += m_objects[i]->getMesh()->vertecies.size();

                //copy data to vbo
                memcpy(vboDataIterator, &data.front(), sizeof(GLfloat) * data.size());
                vboDataIterator += data.size();
            }
            iboDataIterator = nullptr;
            vboDataIterator = nullptr;

            //push ibodata to ibo and vbo
            m_ibo->setData(m_numIndecies, iboData);
            m_vbo->setData(sizeof(GLfloat) * (m_numVertecies*4), vboData);

            delete[] iboData;
            delete[] vboData;


            using namespace CrabEngine::Math;


            //--------------------------------------------------------------
            // draw
            //--------------------------------------------------------------

            m_ibo->bind();
            for(unsigned c = 0; c < m_cams.size(); ++c) {
                Camera* cam = m_cams[c];

                Vec4 viewport = cam->getViewportAsVec4();


                //set up frame buffer and textures
                m_tex0.setWidth(viewport.z * m_window->fbWidth());
                m_tex0.setHeight(viewport.w * m_window->fbHeight());
                m_tex0.Resize();
                m_tex1.setWidth(viewport.z * m_window->fbWidth());
                m_tex1.setHeight(viewport.w * m_window->fbHeight());
                m_tex1.Resize();
                m_fbo.resize(viewport.z * m_window->fbWidth(), viewport.w * m_window->fbHeight());

                Texture* activeTexture = &m_tex0;

                m_fbo.bind();

                m_fbo.setTexture(&m_tex0);

                glClearColor(cam->clearColor.x/255, cam->clearColor.y/255, cam->clearColor.z/255, cam->clearColor.w/255);
                glClear(GL_COLOR_BUFFER_BIT);



                Mat4 projectionMatrix = PerspectiveProjectionMatrix(cam->fov, viewport.z * m_window->fbWidth(), viewport.w * m_window->fbHeight(), 1.0f, 1000.0f);
                Mat4 viewMatrix = cam->getTansformationMatrix();

                //glViewport(viewport.x * m_window->fbWidth(), viewport.y * m_window->fbHeight(), viewport.z * m_window->fbWidth(), viewport.w * m_window->fbHeight());
                glViewport(0, 0, viewport.z * m_window->fbWidth(), viewport.w * m_window->fbHeight());

                unsigned indexOffset = 0;


                for(unsigned o = 0; o < m_objects.size(); ++o) {
                    GraphicsObject2D* obj = m_objects[o];

                    //set object settings
                    obj->getMaterial()->bind();
                    obj->applyUniforms();

                    //get transformation matrix
                    ScaleMatrix scaleMatrix(obj->scale);
                    RotationMatrix2D rotationMatrix(obj->rotation);
                    TranslationMatrix translationMatrix(obj->location);
                    Mat4 MVP = projectionMatrix * viewMatrix * translationMatrix * rotationMatrix * scaleMatrix;

                    //pass transformation matrix to vertex shader
                    obj->getMaterial()->setUniformMat4("MVP", MVP);

                    //set object textures
                    for(unsigned j = 0; j < obj->getTextureCount(); ++j) {
                        obj->getTexture(j).tex->bind(j);
                        obj->getMaterial()->setUniform1i(obj->getTexture(j).name, j);
                    }

                    m_vao->draw(obj->getMesh()->triangles.size(), indexOffset);
                    indexOffset += obj->getMesh()->triangles.size() * sizeof(unsigned);

                    obj->getMaterial()->unbind();
                }
                //glUseProgram(0);

                //TODO: do post processing effects



                m_fbo.unbind();

                m_ibo->unbind();
                m_vao->unbind();

                drawScreenSpaceTexture(activeTexture, viewport, cam->clearColor.w/255);

                m_vao->bind();
                m_ibo->bind();
            }
            m_ibo->unbind();

            m_vao->unbind();

            m_objects.clear();
            m_cams.clear();

            m_window->update();

            glClearColor(0,0,0,1);
            glClear(GL_COLOR_BUFFER_BIT);

        }
    }
}
