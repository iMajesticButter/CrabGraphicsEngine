#include "GLEW/glew.h"

#include "CrabTexture.h"
#include "CrabWindow.h"
#include "CrabRenderer2D.h"
#include "CrabVec2.h"
#include "CrabVec3.h"
#include "CrabVec4.h"
#include "CrabGraphicsUtils.h"

#include <vector>

#define byte unsigned char

int main() {

    using namespace CrabEngine::Graphics;
    using namespace CrabEngine::Math;

    const unsigned width = 500;
    const unsigned height = 500;

    const unsigned windowWidth = 500;
    const unsigned windowHeight = 500;

    const long double moveSpd = 20;

    Window window(Vec2(windowWidth, windowHeight), "texture gen test", false, false, false, false, 4);


    Texture tex(window);

    std::vector<byte> texData;

    Renderer2D renderer(&window);

    long double zoomLevel = 120;

    long double centerPosX = 0;
    long double centerPosY = 0;

    const unsigned iterations = 1000;
    //const Vec2 offset = Vec2(0.5) * Vec2(width, height);
    const long double offsetX = 0.5 * width;
    const long double offsetY = 0.5 * height;

    while(!window.shouldClose()) {


        //Vec2 centerPosPixelCoords = (-centerPos + Vec2(0.5)) * Vec2(width, height) /zoomLevel;
        for(long double y = 0; y < height; ++y) {
            for(long double x = 0; x < width; ++x) {

                Vec3 color;

                //algorithm
                long double cR = ((x-offsetX)/zoomLevel) + centerPosX;
                long double cX = ((y-offsetY)/zoomLevel) + centerPosY;
                long double zR = 0;
                long double zX = 0;
                int iterationsLasted = 0;

                for(unsigned i = 0; i < iterations && zR < 2; ++i) {
                    long double old_zR = zR;
                    zR = (zR*zR) + -1*(zX*zX) + cR;
                    zX = 2*old_zR*zX + cX;

                    ++iterationsLasted;
                }

                if(iterationsLasted == iterations) {
                    color.x = 0;
                    color.y = 0;
                    color.z = 0;
                } else {
                    float hue = ((float)iterationsLasted/(float)iterations)*60.0f;
                    Vec3 h;
                    h.x = (int)(hue*12)%180;
                    h.y = 1;
                    h.z = 1;
                    color = HSVToRGB(h);
                }

                texData.push_back(color.x);
                texData.push_back(color.y);
                texData.push_back(color.z);
            }
        }

        tex.setData(texData, width, height, GL_RGB);
        tex.Init();
        texData.clear();

        renderer.drawScreenSpaceTexture(&tex);

        window.update();

        if(window.keyDown(GLFW_KEY_W)) {
            centerPosY += moveSpd/zoomLevel;
        }
        if(window.keyDown(GLFW_KEY_S)) {
            centerPosY -= moveSpd/zoomLevel;
        }
        if(window.keyDown(GLFW_KEY_A)) {
            centerPosX -= moveSpd/zoomLevel;
        }
        if(window.keyDown(GLFW_KEY_D)) {
            centerPosX += moveSpd/zoomLevel;
        }
        if(window.keyDown(GLFW_KEY_EQUAL)) {
            zoomLevel *= 1.1;
        }
        if(window.keyDown(GLFW_KEY_MINUS)) {
            zoomLevel /= 1.1;
        }

    }

    return 1;
}
