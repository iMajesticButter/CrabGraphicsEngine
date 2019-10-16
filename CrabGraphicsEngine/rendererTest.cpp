#include "CrabRenderer2D.h"
#include "CrabGraphicsObject2D.h"
#include "CrabTexture.h"
#include "CrabMaterial.h"
#include "CrabShader.h"
#include "CrabVec2.h"
#include "CrabVec3.h"
#include "CrabVec4.h"
#include "CrabCamera.h"
#include "CrabWindow.h"

#include <vector>

int main() {
    using namespace CrabEngine::Graphics;
    using namespace CrabEngine::Math;

    Window window(Vec2(-1), "Rendedrer Test", false, false, true, false, true);

    VertexShader vertShader("./shaders/vertShaderTest.vs");
    FragmentShader fragShader("./shaders/fragShaderTest.fs");
    FragmentShader fragShader2("./shaders/fragShaderTest2.fs");

    Material material(window, "material");
    material.AddShader(vertShader);
    material.AddShader(fragShader);
    material.Initialize();

    Material material2(window, "player material");
    material2.AddShader(vertShader);
    material2.AddShader(fragShader2);
    material2.Initialize();

    Texture mrKrabs(window);
    mrKrabs.loadBitmap("textures/crab.bmp");
    mrKrabs.setFilteringMode(LINEAR);
    mrKrabs.Init();

    Texture realKrab(window);
    realKrab.loadBitmap("textures/realCrab.bmp");
    realKrab.setFilteringMode(LINEAR);
    realKrab.Init();

    Texture sponge(window);
    sponge.loadBitmap("textures/sponge.bmp");
    sponge.setFilteringMode(LINEAR);
    sponge.Init();

    Mesh quad;

    std::vector<Vec2> quadVertecies {
        Vec2( 1.0f,  1.0f),
        Vec2( 1.0f, -1.0f),
        Vec2(-1.0f, -1.0f),
        Vec2(-1.0f,  1.0f)
    };

    std::vector<Vec2> quadUV {
        Vec2(1.0f, 1.0f),
        Vec2(1.0f, 0.0f),
        Vec2(0.0f, 0.0f),
        Vec2(0.0f, 1.0f)
    };

    std::vector<unsigned> quadIndices {
        0, 1, 2,
        0, 3, 2
    };

    quad.vertecies = quadVertecies;
    quad.uvCooordinates = quadUV;
    quad.triangles = quadIndices;

    std::vector<GraphicsObject2D*> objects;

    GraphicsObject2D obj1(&quad, &material);
    obj1.setTexture("tex", &mrKrabs);
    obj1.setTexture("tex2", &realKrab);
    obj1.setUniform1f("backTest", 0.25f);
    obj1.setUniform3f("tint", Vec3(1));
    obj1.renderLayer = 0;

    obj1.location = Vec3(0,3,0);

    objects.push_back(&obj1);



    GraphicsObject2D player(&quad, &material2);
    player.setTexture("tex", &sponge);
    player.setUniform3f("tint", Vec3(1));
    player.renderLayer = 1;

    objects.push_back(&player);

    //performance test
    const int w = 30;
    const int h = 30;

    for(unsigned x = 0; x < w; ++x) {
        for(unsigned y = 0; y < h; ++y) {

            GraphicsObject2D* obj = new GraphicsObject2D(&quad, &material);
            obj->setTexture("tex", &mrKrabs);
            obj->setTexture("tex2", &realKrab);
            obj->setUniform1f("backTest", 1.0f);
            obj->setUniform3f("tint", Vec3((float)x/w, (float)y/h, 1));

            obj->renderLayer = -2;
            obj->location = Vec3(x * 0.025f,
                                 y * 0.025f, -3);
            obj->location.z = 10;
            obj->rotation = 0;
            obj->scale = Vec2(0.025f, 0.025f);

            objects.push_back(obj);

        }
    }






    Vec2 PlayerPos(0,0);


    Camera cam;

    Renderer2D renderer(&window);

    while(!window.shouldClose()) {

        cam.location = PlayerPos;
        player.location = PlayerPos;


        material.setUniform2f("mousePos", window.cursorX(), -(window.cursorY()-window.fbHeight()));
        material.setUniform1f("lightRange", 10.0f);

        renderer.start();

        for(unsigned i = 0; i < objects.size(); ++i) {
            renderer.pushObject(objects[i]);
        }
        renderer.pushCamera(&cam);

        renderer.end();

        if(window.keyDown(GLFW_KEY_W)) {
            PlayerPos.y += 0.01f;
        }
        if(window.keyDown(GLFW_KEY_S)) {
            PlayerPos.y -= 0.01f;
        }
        if(window.keyDown(GLFW_KEY_A)) {
            PlayerPos.x -= 0.01f;
        }
        if(window.keyDown(GLFW_KEY_D)) {
            PlayerPos.x += 0.01f;
        }

    }


    return 0;
}
