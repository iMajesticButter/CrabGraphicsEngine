#include <cstring>

#include "CrabGraphicsObject2D.h"

namespace CrabEngine {
    namespace Graphics {


        //---------------------------------------------
        // graphics obj 2d uniform
        //---------------------------------------------

        #define byte unsigned char

        graphicsObj2dUniform::graphicsObj2dUniform(std::string name, unsigned size, void* data, graphicsObj2dUniformType type) :
         m_name(name), m_size(size), m_type(type) {

             m_data = new byte[size];
             memcpy(m_data, data, size);

        }
        graphicsObj2dUniform::graphicsObj2dUniform(const graphicsObj2dUniform& other) :
         m_name(other.m_name), m_size(other.m_size), m_type(other.m_type) {
             m_data = new byte[m_size];
             memcpy(m_data, other.m_data, m_size);
        }
        graphicsObj2dUniform::~graphicsObj2dUniform() {
            delete[] (byte*)m_data;
        }

        graphicsObj2dUniform& graphicsObj2dUniform::operator=(const graphicsObj2dUniform& other) {
            if(m_size != other.m_size) {
                delete[] (byte*)m_data;
                m_data = new byte[other.m_size];
            }
            m_name = other.m_name;
            m_size = other.m_size;
            m_type = other.m_type;
            memcpy(m_data, other.m_data, m_size);
            return *this;
        }

        std::string graphicsObj2dUniform::getName() {
            return m_name;
        }
        unsigned graphicsObj2dUniform::getSize() {
            return m_size;
        }
        graphicsObj2dUniformType graphicsObj2dUniform::getType() {
            return m_type;
        }
        void* graphicsObj2dUniform::getData() {
            return m_data;
        }


        //---------------------------------------------
        // graphics object 2d
        //---------------------------------------------


        GraphicsObject2D::GraphicsObject2D() : m_material(nullptr), m_mesh(nullptr) {

        }
        GraphicsObject2D::GraphicsObject2D(Mesh* mesh, Material* mat) : m_material(mat), m_mesh(mesh) {

        }

        void GraphicsObject2D::setMesh(Mesh* mesh) {
            m_mesh = mesh;
        }
        Mesh* GraphicsObject2D::getMesh() {
            return m_mesh;
        }

        void GraphicsObject2D::setMaterial(Material* mat) {
            m_material = mat;
        }
        Material* GraphicsObject2D::getMaterial() {
            return m_material;
        }

        void GraphicsObject2D::setTexture(std::string name, Texture* tex) {
            graphicsObj2dTex t;
            t.tex = tex;
            t.name = name;
            for(unsigned i = 0; i < m_textures.size(); ++i) {
                if(m_textures[i].name == name) {
                    m_textures[i] = t;
                    return;
                }
            }
            m_textures.push_back(t);
        }
        Texture* GraphicsObject2D::getTexture(std::string name) {
            for(unsigned i = 0; i < m_textures.size(); ++i) {
                if(m_textures[i].name == name) {
                    return m_textures[i].tex;
                }
            }
            return nullptr;
        }
        graphicsObj2dTex GraphicsObject2D::getTexture(unsigned index) {
            return m_textures[index];
        }
        unsigned GraphicsObject2D::getTextureCount() {
            return m_textures.size();
        }
        void GraphicsObject2D::removeTexture(std::string name) {
            for(unsigned i = 0; i < m_textures.size(); ++i) {
                if(m_textures[i].name == name) {
                    m_textures.erase(m_textures.begin() + i);
                    return;
                }
            }
        }

        void GraphicsObject2D::applyUniforms() {

            using namespace CrabEngine::Math;

            for(unsigned i = 0; i < m_uniforms.size(); ++i) {
                std::string name = m_uniforms[i].getName();
                void* data = m_uniforms[i].getData();
                switch(m_uniforms[i].getType()) {
                case float1:
                    m_material->setUniform1f(name, *((float*)data));
                    break;
                case float2:
                    m_material->setUniform2f(name, *((Vec2*)data));
                    break;
                case float3:
                    m_material->setUniform3f(name, *((Vec3*)data));
                    break;
                case float4:
                    m_material->setUniform4f(name, *((Vec4*)data));
                    break;
                case int1:
                    m_material->setUniform1i(name, *((int*)data));
                    break;
                case double1:
                    m_material->setUniform1d(name, *((double*)data));
                    break;
                case mat4:
                    m_material->setUniformMat4(name, *((Mat4*)data));
                    break;
                default:
                    break;
                }

            }
        }

        using namespace CrabEngine::Math;

        void GraphicsObject2D::setUniform1f(std::string name, float data) {
            pushUniform(graphicsObj2dUniform(name, sizeof(float), &data, float1));
        }
        void GraphicsObject2D::setUniform2f(std::string name, CrabEngine::Math::Vec2 data) {
            pushUniform(graphicsObj2dUniform(name, sizeof(Vec2), &data, float2));
        }
        void GraphicsObject2D::setUniform3f(std::string name, CrabEngine::Math::Vec3 data) {
            pushUniform(graphicsObj2dUniform(name, sizeof(Vec3), &data, float3));
        }
        void GraphicsObject2D::setUniform4f(std::string name, CrabEngine::Math::Vec4 data) {
            pushUniform(graphicsObj2dUniform(name, sizeof(Vec4), &data, float4));
        }

        void GraphicsObject2D::setUniform1i(std::string name, int data) {
            pushUniform(graphicsObj2dUniform(name, sizeof(int), &data, int1));
        }
        void GraphicsObject2D::setUniform1d(std::string name, double data) {
            pushUniform(graphicsObj2dUniform(name, sizeof(double), &data, double1));
        }

        void GraphicsObject2D::setUniformMat4(std::string name, CrabEngine::Math::Mat4 data) {
            pushUniform(graphicsObj2dUniform(name, sizeof(Mat4), &data, mat4));
        }

        //------------------------------------------
        // private funcs
        //------------------------------------------

        void GraphicsObject2D::pushUniform(graphicsObj2dUniform uniform) {
            std::string name = uniform.getName();
            for(unsigned i = 0; i < m_uniforms.size(); ++i) {
                if(m_uniforms[i].getName() == name) {
                    m_uniforms[i] = uniform;
                    return;
                }
            }
            m_uniforms.push_back(uniform);
        }

    }
}
