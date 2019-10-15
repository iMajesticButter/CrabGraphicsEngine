#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "CrabWindow.h"
#include "CrabShader.h"
#include "CrabMaterial.h"
#include "CrabVec2.h"
#include "CrabVec3.h"
#include "CrabVec4.h"
#include "CrabMat4.h"
#include "CrabVBO.h"
#include "CrabVAO.h"
#include "CrabIBO.h"
#include "CrabGraphicsUtils.h"
#include "CrabTexture.h"
#include "CrabMesh.h"
#include "CrabGraphicsObject2D.h"
#include "CrabCamera.h"

#define _USE_MATH_DEFINES
#include <math.h>

/*void glfwErrorCallback(int err, const char* description) {
    std::cerr << "ERROR: " << description << std::endl;
}*/

//GLuint vertexBuf[2];
//GLuint VAO;

using CrabEngine::Graphics::VAO;
using CrabEngine::Graphics::VBO;
using CrabEngine::Graphics::IBO;

VBO* vbo = nullptr;
VAO* vao = nullptr;
IBO* ibo = nullptr;

GLuint texture;

void InitOpenGL() {
    using namespace CrabEngine::Graphics;
    /*static const char* vertex_shader_text =
    "#version 330\n"
    "layout(location = 0) in vec3 inPos;\n"
    "void main()\n"
    "{\n"
    "    gl_Position.xyz = inPos;\n"
    "    gl_Position.w = 1.0;\n"
    "}\n";
    static const char* fragment_shader_text =
    "#version 330\n"
    "out vec3 color;\n"
    "uniform vec2 mousePos;\n"
    "void main()\n"
    "{\n"
    "    float dist = distance(mousePos, gl_FragCoord.xy)*0.1;"
    "    color = vec3(gl_FragCoord.x/100, gl_FragCoord.y/100, 0) / dist;\n"
    "}\n";*/

    //triangle
    /*const GLfloat gVertBufData[] = {
        1.0f,   1.0f,       0.0f,       1.0f, 0.0f, 0.0f,
        1.0f,  -1.0f,       0.0f,       0.0f, 1.0f, 0.0f,
       -1.0f,  -1.0f,       0.0f,       0.0f, 0.0f, 1.0f,
       -1.0f,   1.0f,       0.0f,       0.0f, 1.0f, 0.0f
    };*/

    /*const GLfloat gVertBufData[] = {
       //x       y                   r     g     b             s     t          test
         1.0f,   1.0f,               1.0f, 0.0f, 0.0f,         1.0f, 1.0f,      0.0f,
         1.0f,  -1.0f,               0.0f, 1.0f, 0.0f,         1.0f, 0.0f,      0.0f,
        -1.0f,  -1.0f,               0.0f, 0.0f, 1.0f,         0.0f, 0.0f,      0.0f,
        -1.0f,   1.0f,               1.0f, 1.0f, 0.0f,         0.0f, 1.0f,      0.0f
    };*/


    /*const GLuint gVertInxData[] = {
        0, 1, 2,
        0, 3, 2
    };*/

    if(vao != nullptr)
        delete vao;

    vao = new VAO();
    vao->bind();

    if(vbo != nullptr)
        delete vbo;

    vbo = new VBO(VBOusage::STATIC);
    /*vbo->bind();

    VBOlayout layout;
    layout.addAttribute(GL_FLOAT, 2, sizeof(GLfloat));
    layout.addAttribute(GL_FLOAT, 3, sizeof(GLfloat));
    layout.addAttribute(GL_FLOAT, 2, sizeof(GLfloat));
    layout.addAttribute(GL_FLOAT, 1, sizeof(GLfloat));

    vbo->setLayout(layout);
    vbo->setData(sizeof(gVertBufData), gVertBufData);*/

    if(ibo != nullptr)
        delete ibo;

    ibo = new IBO(VBOusage::STATIC);

    //vbo->unbind();
    vao->unbind();

    //load texture
    /*textureData data = CrabEngine::Graphics::loadBitmap("textures/crab.bmp");

    glGenTextures(1, &texture);

    glActiveTexture(GL_TEXTURE0 + 0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, data.width, data.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &data.data.front());
    glGenerateMipmap(GL_TEXTURE_2D);

    data = CrabEngine::Graphics::loadBitmap("textures/realCrab.bmp");

    glGenTextures(1, &texture);

    glActiveTexture(GL_TEXTURE0 + 1);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, data.width, data.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &data.data.front());
    glGenerateMipmap(GL_TEXTURE_2D);*/

    /*const GLfloat gColBufData[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f
    };*/

    //GLuint VAO;
    /*glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //GLint Result = GL_FALSE;
	//int InfoLogLength;

    //create vertex buffer (coordinates)
    glGenBuffers(2, vertexBuf);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuf[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(gVertBufData), gVertBufData, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    //create vertex buffer (colors)
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuf[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(gColBufData), gColBufData, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);*/

    /*GLuint VertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(VertShader, 1, &vertex_shader_text, nullptr);
    glCompileShader(VertShader);

    // Check Vertex Shader
	glGetShaderiv(VertShader, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertShader, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(VertShader, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

    GLuint FragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FragShader, 1, &fragment_shader_text, nullptr);
    glCompileShader(FragShader);

    // Check Fragment Shader
	glGetShaderiv(FragShader, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragShader, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(FragShader, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}*/

    /*GLuint program = glCreateProgram();
    glAttachShader(program, vertShader.getShaderID());
    glAttachShader(program, fragShader.getShaderID());
    glLinkProgram(program);

    // Check the program
	glGetProgramiv(program, GL_LINK_STATUS, &Result);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(program, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

    glDetachShader(program, vertShader.getShaderID());
    glDetachShader(program, fragShader.getShaderID());*/

    //return program;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

bool objSortFunc(CrabEngine::Graphics::GraphicsObject2D* obj1, CrabEngine::Graphics::GraphicsObject2D* obj2) {
    return obj1->renderLayer < obj2->renderLayer;
}

int main() {

    using namespace CrabEngine::Math;
    using namespace CrabEngine::Graphics;

    Window window(Vec2(-1), "TEST", false, false, true, false, true);

    VertexShader vertShader("./shaders/vertShaderTest.vs");
    FragmentShader fragShader("./shaders/fragShaderTest.fs");

    Material testMat(window, "test");
    testMat.AddShader(vertShader);
    testMat.AddShader(fragShader);
    testMat.Initialize();

    Texture tex1(window);
    tex1.loadBitmap("textures/crab.bmp");
    tex1.setFilteringMode(LINEAR);
    tex1.Init();

    Texture tex2(window);
    tex2.loadBitmap("textures/realCrab.bmp");
    tex2.setFilteringMode(LINEAR);
    tex2.Init();


    Mesh mesh;

    std::vector<Vec2> vertecies;
    vertecies.push_back(Vec2( 1.0f,  1.0f));
    vertecies.push_back(Vec2( 1.0f, -1.0f));
    vertecies.push_back(Vec2(-1.0f, -1.0f));
    vertecies.push_back(Vec2(-1.0f,  1.0f));

    std::vector<Vec2> uvCoords;
    uvCoords.push_back(Vec2( 1.0f,  1.0f));
    uvCoords.push_back(Vec2( 1.0f,  0.0f));
    uvCoords.push_back(Vec2( 0.0f,  0.0f));
    uvCoords.push_back(Vec2( 0.0f,  1.0f));

    std::vector<unsigned int> tris{
        0, 1, 2,
        0, 3, 2
    };

    mesh.vertecies = vertecies;
    mesh.uvCooordinates = uvCoords;
    mesh.triangles = tris;

    Vec3 pos(0, 0, 10);
    Vec2 scale(1, 1);
    float rot = 0 * (M_PI/180);

    //std::vector<GLfloat> data = mesh.getVertexData();
    std::vector<GLfloat> data;

    std::cout << vertecies.size() << std::endl;
    std::cout << uvCoords.size() << std::endl;
    std::cout << data.size() << std::endl;

    for(unsigned i = 0; i < data.size(); ++i) {
        std::cout << data[i] << ",";
    }
    std::cout << std::endl;


    std::vector<GraphicsObject2D*> objects;


    float obj1bt = 1.0f;
    float obj2bt = 1.0f;
    float obj3bt = 0.5f;

    GraphicsObject2D obj1(&mesh, &testMat);
    obj1.setTexture("tex", &tex1);
    obj1.setTexture("tex2", &tex2);
    obj1.setUniform1f("backTest", obj1bt);
    obj1.setUniform3f("tint", Vec3(1));

    objects.push_back(&obj1);

    GraphicsObject2D obj2(&mesh, &testMat);
    obj2.setTexture("tex", &tex1);
    obj2.setTexture("tex2", &tex2);
    obj2.setUniform1f("backTest", obj2bt);
    obj2.setUniform3f("tint", Vec3(1));
    obj2.renderLayer = -1;

    objects.push_back(&obj2);

    GraphicsObject2D obj3(&mesh, &testMat);
    obj3.setTexture("tex", &tex1);
    obj3.setTexture("tex2", &tex2);
    obj3.setUniform1f("backTest", obj3bt);
    obj3.setUniform3f("tint", Vec3(1));
    obj3.renderLayer = 1;

    objects.push_back(&obj3);

    const int w = 20;
    const int h = 20;

    for(int x = 0; x < w; ++x) {
        for(int y = 0; y < h; ++y) {

            GraphicsObject2D* obj = new GraphicsObject2D(&mesh, &testMat);
            obj->setTexture("tex", &tex1);
            obj->setTexture("tex2", &tex2);
            obj->setUniform1f("backTest", 1.0f);
            obj->setUniform3f("tint", Vec3((float)x/w, (float)y/h, 1));

            obj->renderLayer = -2;
            obj->location = Vec3((x - ((float)x/2))/w, (y - ((float)y/2))/h, 0)*3;
            obj->location.z = 10;
            obj->rotation = 0;
            obj->scale = Vec2(0.025f, 0.025f);

            objects.push_back(obj);

        }
    }

    Camera cam;

    Vec2 camPos = Vec2(0,0);
    float camRot = 0;
    float camSize = 1;

    /*if(!glfwInit()) {
        std::cerr << "FAILED TO INITIALIZE GLFW!" << std::endl;
    }


    glfwSetErrorCallback(glfwErrorCallback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_SAMPLES, 4);

    GLFWwindow* window = glfwCreateWindow(300, 300, "TEST", nullptr, nullptr);

    if(!window) {
        std::cerr << "WINDOW CONTEXT CREATION FAILED!" << std::endl;
    }

    glfwMakeContextCurrent(window);
    glewInit();*/

    //triangle test

    InitOpenGL();

    bool fullscreen = false;
    bool borderless = false;

    float lightRange = 2;

    bool pressed = false;

    while(!window.shouldClose()) {

        obj1.location = pos;
        obj1.scale = scale;
        obj1.rotation = rot;

        obj2.location = pos + Vec3(2, 0, 0);
        obj2.scale = scale;
        obj2.rotation = rot;

        obj3.location = pos - Vec3(2, 0, 0);
        obj3.scale = scale;
        obj3.rotation = rot;

        cam.location = camPos;
        cam.size = camSize;
        cam.rotation = camRot;

        //testMat.setUniform1i("tex", 0);
        //testMat.setUniform1i("tex2", 1);

        window.update();

        glViewport(0, 0, window.fbWidth(), window.fbHeight());
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);

        //create projection matrix
        PerspectiveProjectionMatrix projMat(cam.fov, window.fbWidth(), window.fbHeight(), 1.0f, 1000.0f);

        //draw triangle test
        //glEnableVertexAttribArray(0);
        //glBindBuffer(GL_ARRAY_BUFFER, VAO);
        //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        //glBindVertexArray(VAO);
        //glUseProgram(program);

        Mat4 camMat = cam.getTansformationMatrix();

        std::sort(objects.begin(), objects.end(), objSortFunc);

        vao->bind();
        for(unsigned i = 0; i < objects.size(); ++i) {
            data = objects[i]->getMesh()->getVertexData();
            vbo->setData(sizeof(GLfloat)*data.size(), &data.front());
            vbo->setLayout(objects[i]->getMesh()->getLayout());

            ibo->setData(sizeof(unsigned int)*objects[i]->getMesh()->triangles.size(), &objects[i]->getMesh()->triangles.front());

            //testMat.bind();
            objects[i]->getMaterial()->bind();
            objects[i]->applyUniforms();

            ScaleMatrix scaleMat(objects[i]->scale);
            RotationMatrix2D rotMat(objects[i]->rotation);
            TranslationMatrix transMat(objects[i]->location);
            Mat4 MVP = projMat * camMat * transMat * rotMat * scaleMat;

            objects[i]->getMaterial()->setUniformMat4("MVP", MVP);
            //objects[i]->getMaterial()->setUniform1f("backTest", 0.5f);


            //tex1.bind(0);
            //tex2.bind(1);

            for(unsigned j = 0; j < objects[i]->getTextureCount(); ++j) {
                objects[i]->getTexture(j).tex->bind(j);
                objects[i]->getMaterial()->setUniform1i(objects[i]->getTexture(j).name, j);
            }

            //vbo->bindAttributeLocations(testMat);
            //glDrawArrays(GL_TRIANGLES, 0, 6);
            vao->draw(objects[i]->getMesh()->triangles.size());
            testMat.unbind();
        }
        ibo->unbind();
        vao->unbind();
        //glDisableVertexAttribArray(0);

        //glBindVertexArray(0);

        //printf("mouseY: %f\n", -(mouseY-height/2));

        //GLint fragMousePos = glGetUniformLocation(program, "mousePos");
        //if(fragMousePos != -1) {
        //    glUniform2f(fragMousePos, window.cursorX(), -(window.cursorY()-window.fbHeight()));
        //}

        //create transformation matrix
        /*ScaleMatrix scaleMat(scale);
        RotationMatrix2D rotMat(rot);
        TranslationMatrix transMat(pos);
        Mat4 MVP = projMat * transMat * rotMat * scaleMat;*/

        /*for(unsigned y = 0; y < 4; ++y) {
            std::cout << "| ";
            for(unsigned x = 0; x < 4; ++x) {
                std::cout << MVP.getVal(x, y) << " ";
            }
            std::cout << "|" << std::endl;
        }
        std::cout << "-----------------------------" << std::endl;*/

        //testMat.setUniformMat4("MVP", MVP);

        testMat.setUniform2f("mousePos", window.cursorX(), -(window.cursorY()-window.fbHeight()));
        testMat.setUniform1f("lightRange", lightRange);

        if(window.keyDown(GLFW_KEY_W)) {
            pos.y += 0.01;
        }
        if(window.keyDown(GLFW_KEY_S)) {
            pos.y -= 0.01;
        }
        if(window.keyDown(GLFW_KEY_A)) {
            pos.x -= 0.01;
        }
        if(window.keyDown(GLFW_KEY_D)) {
            pos.x += 0.01;
        }
        if(window.keyDown(GLFW_KEY_Q)) {
            pos.z += 0.01;
        }
        if(window.keyDown(GLFW_KEY_E)) {
            pos.z -= 0.01;
        }
        if(window.keyDown(GLFW_KEY_UP)) {
            scale.y += 0.01;
        }
        if(window.keyDown(GLFW_KEY_DOWN)) {
            scale.y -= 0.01;
        }
        if(window.keyDown(GLFW_KEY_LEFT)) {
            scale.x += 0.01;
        }
        if(window.keyDown(GLFW_KEY_RIGHT)) {
            scale.x -= 0.01;
        }
        if(window.keyDown(GLFW_KEY_Z)) {
            rot -= 0.01;
        }
        if(window.keyDown(GLFW_KEY_X)) {
            rot += 0.01;
        }
        if(window.keyDown(GLFW_KEY_EQUAL)) {
            lightRange += 0.01;
        }
        if(window.keyDown(GLFW_KEY_MINUS)) {
            lightRange -= 0.01;
            if(lightRange < 0) {
                lightRange = 0;
            }
        }

        if(window.keyDown(GLFW_KEY_I)) {
            camPos.y += 0.01;
        }
        if(window.keyDown(GLFW_KEY_K)) {
            camPos.y -= 0.01;
        }
        if(window.keyDown(GLFW_KEY_J)) {
            camPos.x -= 0.01;
        }
        if(window.keyDown(GLFW_KEY_L)) {
            camPos.x += 0.01;
        }
        if(window.keyDown(GLFW_KEY_U)) {
            camRot -= 0.01;
        }
        if(window.keyDown(GLFW_KEY_O)) {
            camRot += 0.01;
        }
        if(window.keyDown(GLFW_KEY_Y)) {
            camSize += 0.01;
        }
        if(window.keyDown(GLFW_KEY_H)) {
            camSize -= 0.01;
        }
        if(window.keyDown(GLFW_KEY_T)) {
            cam.fov += 0.01;
        }
        if(window.keyDown(GLFW_KEY_G)) {
            cam.fov -= 0.01;
        }

        if(window.keyDown(GLFW_KEY_1) && !pressed) {
            if(obj1bt == 1.0f) {
                obj1bt = 0.5f;
            } else {
                obj1bt = 1.0f;
            }
            obj1.setUniform1f("backTest", obj1bt);
            pressed = true;
        }
        if(window.keyDown(GLFW_KEY_2) && !pressed) {
            if(obj2bt == 1.0f) {
                obj2bt = 0.5f;
            } else {
                obj2bt = 1.0f;
            }
            obj2.setUniform1f("backTest", obj2bt);
            pressed = true;
        }
        if(window.keyDown(GLFW_KEY_3) && !pressed) {
            if(obj3bt == 1.0f) {
                obj3bt = 0.5f;
            } else {
                obj3bt = 1.0f;
            }
            obj3.setUniform1f("backTest", obj3bt);
            pressed = true;
        }

        if(!window.keyDown(GLFW_KEY_1) &&
           !window.keyDown(GLFW_KEY_2) &&
           !window.keyDown(GLFW_KEY_3)) {

            pressed = false;

        }

        if(window.keyDown(GLFW_KEY_ESCAPE)) {
            break;
        } else {
            if(window.keyDown(GLFW_KEY_F)) {
                fullscreen = !fullscreen;
                window.setFullscreen(fullscreen);
                window.initialize();

                InitOpenGL();
            }

            if(window.keyDown(GLFW_KEY_B)) {
                borderless = !borderless;
                window.setBorderless(borderless);
                window.initialize();

                InitOpenGL();
            }
        }
    }

    delete vao;
    delete vbo;
    delete ibo;

    return 0;
}
