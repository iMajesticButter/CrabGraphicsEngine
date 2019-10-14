#include "CrabGraphicsUtils.h"

namespace CrabEngine {
    namespace Graphics {

        textureData loadBitmap(std::string path) {
            FILE* img = fopen(path.c_str(), "rb");

            unsigned char header[54];
            fread(header, sizeof(unsigned char), 54, img);

            unsigned width = *(int*)&header[18];
            unsigned height = *(int*)&header[22];

            const int numChanels = 4;

            unsigned padding=0;
            while ((width*numChanels+padding) % 4 != 0) {
                ++padding;
            }

            unsigned nWidth = width*numChanels+padding;

            unsigned char* data;
            data = new unsigned char[nWidth*numChanels];

            textureData output;

            for(unsigned i = 0; i < height; ++i) {
                fread(data, sizeof(unsigned char), nWidth, img);
                for(unsigned j = 0; j < width*numChanels; j+= numChanels) {
                    output.data.push_back(data[j+2]);
                    output.data.push_back(data[j+1]);
                    output.data.push_back(data[j+0]);
                    output.data.push_back(data[j+3]);
                }
            }

            fclose(img);

            delete[] data;

            output.width = width;
            output.height = height;

            return output;

        }
    }
}
