#ifndef CrabEngine_Graphics_Utils_HEADER
#define CrabEngine_Graphics_Utils_HEADER

#include <vector>
#include <string>

namespace CrabEngine {
    namespace Graphics {

        struct textureData {
            std::vector<unsigned char> data;
            unsigned width, height;
        };

        textureData loadBitmap(std::string path);

    }
}

#endif
