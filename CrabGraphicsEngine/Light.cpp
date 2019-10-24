#include "CrabLight.h"
#include "CrabVec4.h"
#include <math.h>

namespace CrabEngine {
    namespace Graphics {

        Light::Light(CrabEngine::Math::Vec2 loc, CrabEngine::Math::Vec3 _color, float _falloff, float _intencity, float _size, float _softness, bool _castShadows) :
            location(loc), color(_color), falloff(_falloff), intencity(_intencity), size(_size), softness(_softness), castShadows(_castShadows), active(true) {
        }

        CrabEngine::Math::Mat4 Light::getViewMatrix() {
            using namespace CrabEngine::Math;
            float scale = 1/size;
            ScaleMatrix scaleMat(Vec2(scale, scale));
            TranslationMatrix transMat(Vec4(-location, 10.0f, 1.0f));
            return scaleMat * transMat;
        }

    }
}
