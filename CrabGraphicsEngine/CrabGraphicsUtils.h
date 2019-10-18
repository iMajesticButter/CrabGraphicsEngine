#ifndef CrabEngine_Graphics_Utils_HEADER
#define CrabEngine_Graphics_Utils_HEADER

#include <vector>
#include <string>
#include "CrabVec3.h"

namespace CrabEngine {
    namespace Graphics {

        struct textureData {
            std::vector<unsigned char> data;
            unsigned width, height;
        };

        textureData loadBitmap(std::string path);

        CrabEngine::Math::Vec3 HSVToRGB(const CrabEngine::Math::Vec3& hsv);
        CrabEngine::Math::Vec3 RGBtoHSV(const CrabEngine::Math::Vec3& hsv);

    }
}

#endif
