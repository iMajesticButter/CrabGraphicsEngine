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

        Renderer2D::Renderer2D(Window* window, CrabEngine::Math::Vec3 _ambientLight) : ambientLight(_ambientLight), m_window(window), m_screenSpaceImageMat(*window, "Screen Space Image"),
                m_screenSpaceImageFrag("./internalShaders/screenSpaceImage.fs"),
                m_screenSpaceImageVert("./internalShaders/screenSpaceImage.vs"),
                m_fbo(window),
                m_tex0(*window),
                m_tex1(*window),
                m_lightFBO(window),
                m_shadowCasterTex(*window),
                m_shadowMapTex(*window),
                m_lightsTex(*window),
                m_shadowMapFrag("./internalShaders/shadowMap.fs"),
                m_shadowMapVert("./internalShaders/shadowMap.vs"),
                m_shadowMapMat(*window, "Shadow Map Material"),
                m_lightFrag("./internalShaders/light.fs"),
                m_lightVert("./internalShaders/light.vs"),
                m_lightMat(*window, "Light Material") {
            windowInitEventCallback callback;
            callback.context = this;
            callback.func = InitCallback;
            m_window->registerInitFunc(callback);

            m_screenSpaceImageMat.AddShader(m_screenSpaceImageFrag);
            m_screenSpaceImageMat.AddShader(m_screenSpaceImageVert);
            m_screenSpaceImageMat.Initialize();

            m_shadowMapMat.AddShader(m_shadowMapVert);
            m_shadowMapMat.AddShader(m_shadowMapFrag);
            m_shadowMapMat.Initialize();

            m_lightMat.AddShader(m_lightVert);
            m_lightMat.AddShader(m_lightFrag);
            m_lightMat.Initialize();

            m_tex0.setFilteringMode(LINEAR);
            m_tex1.setFilteringMode(LINEAR);

            m_shadowCasterTex.setFilteringMode(LINEAR);
            m_shadowMapTex.setFilteringMode(LINEAR);
            m_lightsTex.setFilteringMode(LINEAR);

            //set start time
            m_startTime = std::chrono::steady_clock::now();

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
        void Renderer2D::drawScreenSpaceTexture(Texture* tex, CrabEngine::Math::Vec4 viewport, float alpha, unsigned fbWidth, unsigned fbHeight) {
            if(fbWidth == 0)
                fbWidth = m_window->fbWidth();
            if(fbHeight == 0)
                fbHeight = m_window->fbHeight();

            glViewport(0, 0, fbWidth, fbHeight);

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
            m_lights.clear();
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
        void Renderer2D::pushLight(Light* light) {
            if(light->active) {
                m_lights.push_back(light);
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

                if(obj->castShadows) {
                    //m_shadowCasters.push_back(obj);

                    m_numVerteciesShadowCasters += obj->getMesh()->vertecies.size();
                    m_numIndeciesShadowCasters += obj->getMesh()->triangles.size();
                }
            }
        }


        void Renderer2D::end(Texture* outputTexture) {
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

            //push data to ibo and vbo
            m_ibo->setData(m_numIndecies, iboData);
            m_vbo->setData(sizeof(GLfloat) * (m_numVertecies*4), vboData);

            delete[] iboData;
            delete[] vboData;


            using namespace CrabEngine::Math;


            //--------------------------------------------------------------
            // draw
            //--------------------------------------------------------------

            //setup output texture
            unsigned fbWidth = m_window->fbWidth();
            unsigned fbHeight = m_window->fbHeight();

            bool outTex = false;
            if(outputTexture != nullptr) {
                outTex = true;

                fbWidth  = outputTexture->getWidth();
                fbHeight = outputTexture->getHeight();

                fbWidth  = fbWidth  == 0 ? 1 : fbWidth;
                fbHeight = fbHeight == 0 ? 1 : fbHeight;

                outputTexture->setFormat(GL_RGBA);
                outputTexture->Resize();

                m_fbo.resize(fbWidth, fbHeight);

                m_fbo.bind();

                m_fbo.setTexture(outputTexture);
                glClearColor(0,0,0,1);
                glClear(GL_COLOR_BUFFER_BIT);

                m_fbo.unbind();

            }

            std::chrono::duration<double> time = std::chrono::steady_clock::now() - m_startTime;
            m_time = time.count();

            for(unsigned c = 0; c < m_cams.size(); ++c) {
                Camera* cam = m_cams[c];

                Vec4 viewport = cam->getViewportAsVec4();

                Mat4 projectionMatrix = PerspectiveProjectionMatrix(cam->fov, viewport.z * fbWidth, viewport.w * fbHeight, 1.0f, 1000.0f);
                Mat4 projectionMatrix1to1 = PerspectiveProjectionMatrix(cam->fov, 1, 1, 1.0f, 1000.0f);
                Mat4 viewMatrix = cam->getTansformationMatrix();

                unsigned indexOffset = 0;

                m_vao->bind();
                m_ibo->bind();


                //--------------------------------------------------------
                // Lighting
                //--------------------------------------------------------

                //generate light texture (a texture that contains all the lit up areas and their colors)
                m_lightsTex.setWidth(viewport.z * fbWidth);
                m_lightsTex.setHeight(viewport.w * fbHeight);
                m_lightsTex.Resize();

                m_lightFBO.resize(viewport.z * fbWidth, viewport.w * fbHeight);

                m_lightFBO.bind();
                m_lightFBO.setTexture(&m_lightsTex);

                glClearColor(ambientLight.x, ambientLight.y, ambientLight.z, 0);
                glClearColor(0, 0, 0, 0);
                glClear(GL_COLOR_BUFFER_BIT);

                for(unsigned l = 0; l < m_lights.size(); ++l) {
                    Light* light = m_lights[l];

                    unsigned res = light->getShadowTextureResolution();

                    //render shadow casters to screen with light in the middle
                    m_shadowCasterTex.setWidth(res);
                    m_shadowCasterTex.setHeight(res);
                    m_shadowCasterTex.Resize();
                    m_shadowMapTex.setWidth(res);
                    m_shadowMapTex.setHeight(1);
                    m_shadowMapTex.Resize();

                    m_lightFBO.resize(res, res);

                    m_lightFBO.setTexture(&m_shadowCasterTex);
                    glClear(GL_COLOR_BUFFER_BIT);

                    glViewport(0, 0, res, res);

                    Mat4 lightMatrix = light->getViewMatrix();

                    m_ibo->bind();
                    m_vao->bind();
                    //draw all shadow casters to shadowCasterTex centered on the light position
                    for(unsigned o = 0; o < m_objects.size(); ++o) {
                        GraphicsObject2D* obj = m_objects[o];
                        if(!obj->castShadows) {
                            indexOffset += obj->getMesh()->triangles.size() * sizeof(unsigned);
                            continue;
                        }

                        //set object settings
                        obj->getMaterial()->bind();
                        obj->applyUniforms();

                        //get transformation matrix
                        ScaleMatrix scaleMatrix(obj->scale);
                        RotationMatrix2D rotationMatrix(obj->rotation);
                        TranslationMatrix translationMatrix(obj->location);
                        Mat4 MVP = projectionMatrix1to1 * lightMatrix * translationMatrix * rotationMatrix * scaleMatrix;

                        //pass transformation matrix to vertex shader
                        obj->getMaterial()->setUniformMat4("MVP", MVP);
                        obj->getMaterial()->setUniform1f("Time_ms", m_time);

                        //set object textures
                        for(unsigned j = 0; j < obj->getTextureCount(); ++j) {
                            obj->getTexture(j).tex->bind(j);
                            obj->getMaterial()->setUniform1i(obj->getTexture(j).name, j);
                        }

                        m_vao->draw(obj->getMesh()->triangles.size(), indexOffset);
                        indexOffset += obj->getMesh()->triangles.size() * sizeof(unsigned);

                        obj->getMaterial()->unbind();
                    }
                    m_ibo->unbind();
                    m_vao->unbind();

                    //generate shadow map
                    m_lightFBO.resize(res, 1);
                    m_lightFBO.setTexture(&m_shadowMapTex);
                    glClear(GL_COLOR_BUFFER_BIT);

                    glViewport(0, 0, res, 1);

                    m_shadowMapMat.setUniform2f("resolution", res, 1);

                    drawPostEffectQuad(&m_shadowCasterTex, &m_shadowMapMat);

                    //draw the light to the screen
                    //DEBUG: not transforming light atm

                    m_lightFBO.resize(viewport.z * fbWidth, viewport.w * fbHeight);
                    m_lightFBO.setTexture(&m_lightsTex);

                    glViewport(0, 0, viewport.z * fbWidth, viewport.w * fbHeight);

                    m_lightMat.setUniform3f("lightColor", light->color);
                    m_lightMat.setUniform2f("resolution", res, res);
                    m_lightMat.setUniform2f("lightPos", light->location);
                    m_lightMat.setUniform1f("falloff", light->falloff);
                    m_lightMat.setUniform1f("intencity", light->intencity);

                    drawPostEffectQuad(&m_shadowMapTex, &m_lightMat);


                }

                m_lightFBO.unbind();

                drawScreenSpaceTexture(&m_shadowCasterTex, Vec4(0,0,1,1), 0);
                drawScreenSpaceTexture(&m_lightsTex, Vec4(0,0,1,1), 0);

                continue;






                //--------------------------------------------------------
                // Rendering
                //--------------------------------------------------------

                m_ibo->bind();
                m_vao->bind();

                //render all objects to the screen

                //set up frame buffer and textures
                m_tex0.setWidth(viewport.z * fbWidth);
                m_tex0.setHeight(viewport.w * fbHeight);
                m_tex0.Resize();
                m_tex1.setWidth(viewport.z * fbWidth);
                m_tex1.setHeight(viewport.w * fbHeight);
                m_tex1.Resize();
                m_fbo.resize(viewport.z * fbWidth, viewport.w * fbHeight);

                Texture* activeTexture = &m_tex0;

                m_fbo.bind();

                m_fbo.setTexture(&m_tex0);

                glClearColor(cam->clearColor.x/255, cam->clearColor.y/255, cam->clearColor.z/255, cam->clearColor.w/255);
                glClear(GL_COLOR_BUFFER_BIT);

                //glViewport(viewport.x * m_window->fbWidth(), viewport.y * m_window->fbHeight(), viewport.z * m_window->fbWidth(), viewport.w * m_window->fbHeight());
                glViewport(0, 0, viewport.z * fbWidth, viewport.w * fbHeight);

                indexOffset = 0;

                m_ibo->bind();
                m_vao->bind();

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
                    obj->getMaterial()->setUniform1f("Time_ms", m_time);

                    //set object textures
                    for(unsigned j = 0; j < obj->getTextureCount(); ++j) {
                        obj->getTexture(j).tex->bind(j);
                        obj->getMaterial()->setUniform1i(obj->getTexture(j).name, j);
                    }

                    m_vao->draw(obj->getMesh()->triangles.size(), indexOffset);
                    indexOffset += obj->getMesh()->triangles.size() * sizeof(unsigned);

                    obj->getMaterial()->unbind();
                }

                m_ibo->unbind();
                m_vao->unbind();

                //do post processing effects

                std::vector<PostEffect*> postEffects = cam->getPostEffects();
                Texture* lastTexture;

                for(unsigned i = 0; i < postEffects.size(); ++i) {
                    PostEffect* effect = postEffects[i];
                    if(!effect->active)
                        continue;

                    //toggle between textures (need to do this because you cant draw to the same texture that you are drawing)
                    lastTexture = activeTexture;
                    if(activeTexture == &m_tex0) {
                        activeTexture = &m_tex1;
                    } else {
                        activeTexture = &m_tex0;
                    }
                    m_fbo.setTexture(activeTexture);

                    //draw post processing effect
                    drawPostEffectQuad(lastTexture, effect->getMaterial());

                }

                lastTexture = nullptr;

                //finally, draw to screen!
                if(outTex) {
                    m_fbo.unbind();
                    m_fbo.resize(fbWidth, fbHeight);
                    m_fbo.bind();
                    m_fbo.setTexture(outputTexture);
                } else {
                    m_fbo.unbind();
                }

                glViewport(0, 0, fbWidth, fbHeight);
                drawScreenSpaceTexture(activeTexture, viewport, cam->clearColor.w/255, fbWidth, fbHeight);
                activeTexture = nullptr;

                if(outTex) {
                    m_fbo.unbind();
                }
            }
            m_ibo->unbind();

            m_vao->unbind();

            m_objects.clear();
            m_lights.clear();
            m_cams.clear();

            if(!outTex) {
                m_window->update();

                glClearColor(0,0,0,1);
                glClear(GL_COLOR_BUFFER_BIT);
            }

        }

        void Renderer2D::drawPostEffectQuad(Texture* tex, Material* mat) {
            //glViewport(0, 0, m_window->fbWidth(), m_window->fbHeight());

            tex->bind(0);

            mat->setUniform1i("frame", 0);
            mat->setUniform1f("Time_ms", m_time);

            m_vaoQuad->bind();
            m_iboQuad->bind();
            mat->bind();
            m_vaoQuad->draw(6);
            mat->unbind();
            m_iboQuad->unbind();
            m_vaoQuad->unbind();
        }

    }
}
