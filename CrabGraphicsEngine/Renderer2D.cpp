#include "GLEW/glew.h"

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

        Renderer2D::Renderer2D(Window* window) : m_window(window) {
            windowInitEventCallback callback;
            callback.context = this;
            callback.func = InitCallback;
            m_window->registerInitFunc(callback);

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
            m_vbo = new VBO(VBOusage::STATIC);
            m_vbo->bind();
            m_ibo = new IBO(VBOusage::STATIC);

            //set vbo layout
            VBOlayout layout;
            layout.addAttribute(GL_FLOAT, 2, sizeof(GLfloat));
            layout.addAttribute(GL_FLOAT, 2, sizeof(GLfloat));

            m_vbo->setLayout(layout);

            m_vao->unbind();

            //enable blending
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
            const unsigned vertexSize = sizeof(GLfloat)*4;

            //resize vbo if required
            if(m_numVertecies * vertexSize != m_vbo->getSize()) {
                //m_vbo->resize(m_numVertecies * vertexSize);
            }

            //set vbo and ibo data
            unsigned* iboData = new unsigned[m_numIndecies];
            unsigned* iboDataIterator = iboData;

            //test-------------------------
            float* vboData = new float[m_numVertecies*4];
            float* vboDataIterator = vboData;

            std::vector<GLfloat> data;

            unsigned offset = 0;

            //byte* vboPtr = (byte*)m_vbo->getPointerInternal();
            for(unsigned i = 0; i < m_objects.size(); ++i) {
                //copy data to vbo
                data = m_objects[i]->getMesh()->getVertexData();

                //unsigned size = sizeof(GLfloat) * data.size();

                //memcpy(vboPtr, &data.front(), size);
                //vboPtr += size;

                //copy data to ibo
                //memcpy(iboDataIterator, &(m_objects[i]->getMesh()->triangles.front()), sizeof(unsigned) * m_objects[i]->getMesh()->triangles.size());
                for(unsigned j = 0; j < m_objects[i]->getMesh()->triangles.size(); ++j) {
                    *(iboDataIterator + j) = m_objects[i]->getMesh()->triangles[j] + offset;
                }
                iboDataIterator += m_objects[i]->getMesh()->triangles.size();
                offset += m_objects[i]->getMesh()->vertecies.size();

                //test---------------------------------
                memcpy(vboDataIterator, &data.front(), sizeof(GLfloat) * data.size());
                vboDataIterator += data.size();
            }
            //m_vbo->releasePointer();
            //vboPtr = nullptr;
            iboDataIterator = nullptr;
            //test------------------------------------
            vboDataIterator = nullptr;

            //std::cout << "SETTING IBO DATA: " << m_numIndecies * sizeof(unsigned) << std::endl;
            //push ibodata to ibo
            m_ibo->setData(m_numIndecies, iboData);
            //std::cout << "DONE SETTING IBO DATA" << std::endl;
            //std::cout << "SETTING VBO DATA" << std::endl;
            //test--------------------------
            m_vbo->setData(sizeof(GLfloat) * (m_numVertecies*4), vboData);
            //std::cout << "DONE SETTING VBO DATA" << std::endl;

            delete[] iboData;
            //test-----------------------------
            delete[] vboData;


            using namespace CrabEngine::Math;


            //--------------------------------------------------------------
            // draw
            //--------------------------------------------------------------

            //std::cout << "SWAPPING BUFFERS" << std::endl;
            m_window->update();
            //std::cout << "DONE SWAPPING BUFFERS" << std::endl;

            glClear(GL_COLOR_BUFFER_BIT);

            for(unsigned c = 0; c < m_cams.size(); ++c) {
                Camera* cam = m_cams[c];

                Vec4 viewport = cam->getViewportAsVec4();

                Mat4 projectionMatrix = PerspectiveProjectionMatrix(cam->fov, viewport.z * m_window->fbWidth(), viewport.w * m_window->fbHeight(), 1.0f, 1000.0f);
                Mat4 viewMatrix = cam->getTansformationMatrix();

                glViewport(viewport.x * m_window->fbWidth(), viewport.y * m_window->fbHeight(), viewport.z * m_window->fbWidth(), viewport.w * m_window->fbHeight());

                unsigned indexOffset = 0;

                m_ibo->bind();
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
                m_ibo->unbind();

            }

            m_vao->unbind();

            m_objects.clear();
            m_cams.clear();

        }
    }
}
