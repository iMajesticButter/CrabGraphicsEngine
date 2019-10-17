#ifndef CrabEngine_Graphics_PostEffect_HEADER
#define CrabEngine_Graphics_PostEffect_HEADER

#include "CrabMaterial.h"

namespace CrabEngine {
    namespace Graphics {

        class PostEffect {
        public:

            bool active;

            PostEffect();
            PostEffect(Material* mat);

            Material* getMaterial();
            void setMaterial(Material* mat);

        private:

            Material* m_mat;

        };
    }
}

#endif
