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
#include "CrabPostEffect.h"
#include "CrabLight.h"

#include <vector>
#include <iostream>

int main() {
    using namespace CrabEngine::Graphics;
    using namespace CrabEngine::Math;

    Window window(Vec2(-1), "Rendedrer Test", false, false, true, false, 4);

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

    VertexShader postVert("./shaders/postEffectTest.vs");
    FragmentShader postFrag("./shaders/postEffectTest.fs");

    Material postEffectMat(window, "Post Effect Test");
    postEffectMat.AddShader(postVert);
    postEffectMat.AddShader(postFrag);
    postEffectMat.Initialize();

    VertexShader passThruVert("./internalShaders/postEffectPassThru.vs");
    FragmentShader lightingPostFrag("./internalShaders/EffectLighting.fs");

    Material lightingPostEffectMat(window, "post effect that applies lighting to the whole screen");
    lightingPostEffectMat.AddShader(passThruVert);
    lightingPostEffectMat.AddShader(lightingPostFrag);
    lightingPostEffectMat.Initialize();

    FragmentShader ditherFrag("./internalShaders/EffectDither.fs");

    Material ditherMat(window, "dithering post effect");
    ditherMat.AddShader(passThruVert);
    ditherMat.AddShader(ditherFrag);
    ditherMat.Initialize();

    PostEffect postEffectTest(&postEffectMat);
    PostEffect lightingPostEffect(&lightingPostEffectMat);
    PostEffect dither(&ditherMat);

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

    Texture scene(window);
    scene.setWidth(20);
    scene.setHeight(20);
    scene.setFilteringMode(NEAREST);
    scene.Init();

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
    player.setTexture("tex", &mrKrabs);
    player.setUniform3f("tint", Vec3(1));
    player.renderLayer = 1;
    player.castShadows = true;

    objects.push_back(&player);

    //performance test
    const int w = 10;
    const int h = 10;

    for(unsigned x = 0; x < w; ++x) {
        for(unsigned y = 0; y < h; ++y) {

            GraphicsObject2D* obj = new GraphicsObject2D(&quad, &material);
            obj->setTexture("tex", &mrKrabs);
            obj->setTexture("tex2", &realKrab);
            obj->setUniform1f("backTest", 1.0f);
            obj->setUniform3f("tint", Vec3((float)x/w, (float)y/h, 1));

            obj->renderLayer = 2;
            obj->location = Vec3(-5+x * 3,
                                 -5+y * 3, -3);
            obj->location.z = 0;
            obj->rotation = 0;
            obj->scale = Vec2(0.25f, 0.25f);
            obj->castShadows = true;

            objects.push_back(obj);

        }
    }


    Vec2 PlayerPos(0,0);


    Camera cam;
    cam.clearColor = Vec4(255, 255, 255, 255);
    cam.addPostEffect(&lightingPostEffect);
    cam.addPostEffect(&dither);
    //cam.setViewportPos(-0.5, 0, 0.5, 1);
    cam.setViewportPos(0, 0, 0.5, 1);
    //cam.addPostEffect(&postEffectTest);
    //cam.addPostEffect(&postEffectTest);
    //cam.addPostEffect(&postEffectTest);
    Camera cam3;
    cam3.clearColor = Vec4(255, 255, 255, 255);
    cam3.addPostEffect(&lightingPostEffect);
    cam3.addPostEffect(&dither);
    cam3.setViewportPos(0.5, 0, 0.5, 1);
    //cam.addPostEffect(&postEffectTest);
    //cam.addPostEffect(&postEffectTest);
    //cam.addPostEffect(&postEffectTest);
    Camera cam2;
    cam2.clearColor = Vec4(255, 255, 255, 255);
    cam2.renderLayer = 1;
    cam2.addPostEffect(&lightingPostEffect);
    cam2.addPostEffect(&dither);
    cam2.addPostEffect(&postEffectTest);
    cam2.setViewportPos(0.75, 0.75, 0.25, 0.25);

    Light l;
    l.size = 2;
    l.softness = 2;
    l.location = Vec2(1,1);
    l.castShadows = true;
    l.intencity = 1;
    l.falloff = 1;

    Light l2;
    l2.color = Vec3(1,1,0);
    l2.castShadows = true;
    l2.location = Vec2(2,3);

    Renderer2D renderer(&window, Vec3(0,0,0));

    bool fullscreen = false;
    bool pressed = false;

    //fps counter setup
    auto last = std::chrono::high_resolution_clock::now();

    const unsigned fpsSamples = 100;
    unsigned sampleCount = 0;
    double averageDT = 0;

    while(!window.shouldClose()) {

        //fps counter
        std::chrono::duration<double> time = std::chrono::high_resolution_clock::now() - last;
        double dt = time.count();
        last = std::chrono::high_resolution_clock::now();

        ++sampleCount;
        averageDT += dt;
        if(sampleCount >= fpsSamples) {
            double fps = fpsSamples / averageDT;
            sampleCount = 0;
            std::cout << "Average FPS: " << fps << std::endl;
            averageDT = 0;
        }

        cam.location = PlayerPos;
        //player.location = PlayerPos;
        l.location = PlayerPos;


        material.setUniform2f("mousePos", window.cursorX(), -(window.cursorY()-window.fbHeight()));
        material.setUniform1f("lightRange", 10.0f);

        renderer.start();


        for(unsigned i = 0; i < objects.size(); ++i) {
            renderer.pushObject(objects[i]);
        }

        renderer.pushLight(&l);
        renderer.pushLight(&l2);

        renderer.pushCamera(&cam);
        renderer.pushCamera(&cam3);

        //renderer.drawScreenSpaceTexture(&sponge, Vec4(0, 0, 1, 1));
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
        if(window.keyDown(GLFW_KEY_UP)) {
            cam.fov += 2;
        }
        if(window.keyDown(GLFW_KEY_DOWN)) {
            cam.fov -= 2;
        }
        if(window.keyDown(GLFW_KEY_LEFT)) {
            cam.rotation += 0.01f;
        }
        if(window.keyDown(GLFW_KEY_RIGHT)) {
            cam.rotation -= 0.01f;
        }
        if(window.keyDown(GLFW_KEY_EQUAL)) {
            l.size += 0.01f;
        }
        if(window.keyDown(GLFW_KEY_MINUS)) {
            l.size -= 0.01f;
        }
        if(window.keyDown(GLFW_KEY_LEFT_BRACKET)) {
            cam.size += 0.01f;
        }
        if(window.keyDown(GLFW_KEY_RIGHT_BRACKET)) {
            cam.size -= 0.01f;
        }

        if(window.keyDown(GLFW_KEY_O)) {
            l.intencity += 0.01f;
        }
        if(window.keyDown(GLFW_KEY_L)) {
            l.intencity -= 0.01f;
        }
        if(window.keyDown(GLFW_KEY_I)) {
            l.falloff += 0.01f;
        }
        if(window.keyDown(GLFW_KEY_K)) {
            l.falloff -= 0.01f;
        }

        if(window.keyDown(GLFW_KEY_F11)) {
            if(!pressed) {
                fullscreen = !fullscreen;
                window.setFullscreen(fullscreen);
                window.initialize();
            }
            pressed = true;
        } else {
            pressed = false;
        }

    }


    return 0;
}
