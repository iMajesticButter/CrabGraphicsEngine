#include "GLEW/glew.h"

#include "CrabTexture.h"
#include "CrabWindow.h"
#include "CrabRenderer2D.h"
#include "CrabVec2.h"
#include "CrabVec3.h"
#include "CrabVec4.h"

#include <vector>

#define byte unsigned char

int main() {

    using namespace CrabEngine::Graphics;
    using namespace CrabEngine::Math;

    const unsigned width = 500;
    const unsigned height = 500;

    Window window(Vec2(width, height), "texture gen test", false, false, false, false, 4);


    Texture tex(window);

    std::vector<byte> texData;

    Renderer2D renderer(&window);


    while(!window.shouldClose()) {

        for(unsigned i = 0; i < (width*3) * (height*3); ++i) {
            byte dat = rand() % 255;
            texData.push_back(dat);
            texData.push_back(dat);
            texData.push_back(dat);
        }

        tex.setData(texData, width, height, GL_RGB);
        tex.Init();
        texData.clear();

        renderer.drawScreenSpaceTexture(&tex);

        window.update();

    }

    return 1;
}
