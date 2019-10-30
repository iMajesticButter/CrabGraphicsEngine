#ifndef CrabEngine_Graphics_GraphicsObject2D_HEADER
#define CrabEngine_Graphics_GraphicsObject2D_HEADER

#include "CrabMesh.h"
#include "CrabVec2.h"
#include "CrabTexture.h"
#include "CrabMaterial.h"
#include "CrabMat4.h"

#include <vector>
#include <string>

namespace CrabEngine {
    namespace Graphics {

        struct graphicsObj2dTex {
            Texture* tex;
            std::string name;
        };

        enum graphicsObj2dUniformType {
            float1,
            float2,
            float3,
            float4,
            int1,
            double1,
            mat4
        };

        class graphicsObj2dUniform {
        public:
            graphicsObj2dUniform(std::string name, unsigned size, void* data, graphicsObj2dUniformType type);
            graphicsObj2dUniform(const graphicsObj2dUniform& other);
            ~graphicsObj2dUniform();

            graphicsObj2dUniform& operator=(const graphicsObj2dUniform& other);

            std::string* getName();
            unsigned getSize();
            graphicsObj2dUniformType getType();
            void* getData();
        private:
            std::string m_name;
            unsigned m_size;
            void* m_data;
            graphicsObj2dUniformType m_type;
        };

        class GraphicsObject2D {
        public:

            CrabEngine::Math::Vec3 location;
            CrabEngine::Math::Vec2 scale;

            //! rotation in radians
            float rotation;

            //! larger = on top
            int renderLayer = 0;

            bool visible;
            bool castShadows;

            CrabEngine::Math::Mat4 transformMatrix;

            GraphicsObject2D();
            GraphicsObject2D(Mesh* mesh, Material* mat);

            void setMesh(Mesh* mesh);
            Mesh* getMesh();

            void setMaterial(Material* mat);
            Material* getMaterial();

            void setTexture(std::string name, Texture* tex);
            Texture* getTexture(std::string name);
            graphicsObj2dTex getTexture(unsigned index);
            unsigned getTextureCount();
            void removeTexture(std::string name);

            void calculateTransformMatrix();

            bool texturesEqual(const GraphicsObject2D& other) const;

            void applyUniforms();

            void setUniform1f(std::string name, float data);
            void setUniform2f(std::string name, CrabEngine::Math::Vec2 data);
            void setUniform3f(std::string name, CrabEngine::Math::Vec3 data);
            void setUniform4f(std::string name, CrabEngine::Math::Vec4 data);

            void setUniform1i(std::string name, int data);
            void setUniform1d(std::string name, double data);

            void setUniformMat4(std::string name, CrabEngine::Math::Mat4 data);

        private:

            //old loc/rot/scale to detect if they have changed
            CrabEngine::Math::Vec3 m_OLDlocation;
            CrabEngine::Math::Vec2 m_OLDscale;

            //matrix components
            CrabEngine::Math::Mat4 m_transMat;
            CrabEngine::Math::Mat4 m_rotMat;
            CrabEngine::Math::Mat4 m_scaleMat;

            //! rotation in radians
            float m_OLDrotation;

            void pushUniform(graphicsObj2dUniform uniform);

            std::vector<graphicsObj2dTex> m_textures;
            std::vector<graphicsObj2dUniform> m_uniforms;

            Material* m_material = nullptr;
            Mesh* m_mesh = nullptr;


        };

    }
}

#endif
