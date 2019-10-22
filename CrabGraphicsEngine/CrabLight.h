#ifndef CrabEngine_Graphics_Light_HEADER
#define CrabEngine_Graphics_Light_HEADER

#include "CrabVec2.h"
#include "CrabVec3.h"
#include "CrabMat4.h"

namespace CrabEngine {
    namespace Graphics {

        class Light {
        public:

            CrabEngine::Math::Vec2 location;
            CrabEngine::Math::Vec3 color;
            float falloff;
            float intencity;
            float size;
            float softness;

            bool castShadows;
            bool active;

            Light(CrabEngine::Math::Vec2 loc = CrabEngine::Math::Vec2(0,0), CrabEngine::Math::Vec3 color = CrabEngine::Math::Vec3(1,1,1), float falloff = 1, float intencity = 1, float size = 1, float softness = 0.25, bool castShadows = false);

            //! set the shadow resolution level, the shadow resolution will be 2 to the power of this number
            /*!
              This number has a max value of 10!
            */
            void setShadowResolution(unsigned res);

            unsigned getShadowTextureResolution();

            CrabEngine::Math::Mat4 getViewMatrix();

        private:

            unsigned m_shadowResolution;

        };

    }
}

#endif
