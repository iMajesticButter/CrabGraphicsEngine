#include "CrabLight.h"
#include "CrabVec4.h"
#include <math.h>

namespace CrabEngine {
    namespace Graphics {

        Light::Light(CrabEngine::Math::Vec2 loc, CrabEngine::Math::Vec3 _color, float _falloff, float _intencity, float _size, float _softness, bool _castShadows) :
            location(loc), color(_color), falloff(_falloff), intencity(_intencity), size(_size), softness(_softness), castShadows(_castShadows), active(true), m_shadowResolution(256) {
        }

        //! set the shadow resolution level, the shadow resolution will be 2 to the power of this number
        void Light::setShadowResolution(unsigned res) {
            m_shadowResolution = pow(2, std::min(res, 10u));
        }

        unsigned Light::getShadowTextureResolution() {
            return m_shadowResolution;
        }

        CrabEngine::Math::Mat4 Light::getViewMatrix() {
            using namespace CrabEngine::Math;
            TranslationMatrix transMat(Vec4(-location, 10.0f, 1.0f));
            return transMat;
        }

    }
}
