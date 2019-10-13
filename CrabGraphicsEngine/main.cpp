#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
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


    const GLuint gVertInxData[] = {
        0, 1, 2,
        0, 3, 2
    };

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

    ibo = new IBO(gVertInxData, 6);

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
    vertecies.push_back(Vec2(-1.0f,  1.0f));
    vertecies.push_back(Vec2( 1.0f, -1.0f));
    vertecies.push_back(Vec2(-1.0f, -1.0f));

    std::vector<Vec3> vertColors;
    vertColors.push_back(Vec3( 1.0f,  0.0f,  0.0f));
    vertColors.push_back(Vec3( 0.0f,  1.0f,  0.0f));
    vertColors.push_back(Vec3( 0.0f,  0.0f,  1.0f));
    vertColors.push_back(Vec3( 0.0f,  1.0f,  0.0f));

    std::vector<Vec2> uvCoords;
    uvCoords.push_back(Vec2( 1.0f,  1.0f));
    uvCoords.push_back(Vec2( 0.0f,  1.0f));
    uvCoords.push_back(Vec2( 1.0f,  0.0f));
    uvCoords.push_back(Vec2( 0.0f,  0.0f));

    std::vector<unsigned int> tris = {
        0, 1, 2,
        0, 3, 2
    };

    mesh.vertecies = vertecies;
    mesh.colors = vertColors;
    mesh.uvCooordinates = uvCoords;
    mesh.triangles = tris;

    Vec3 pos(0, 0, 10);
    Vec2 scale(1, 1);
    float rot = 0 * (M_PI/180);



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

    while(!window.shouldClose()) {

        testMat.setUniform1i("tex", 0);
        testMat.setUniform1i("tex2", 1);

        window.update();

        glViewport(0, 0, window.fbWidth(), window.fbHeight());
        glClear(GL_COLOR_BUFFER_BIT);

        //create projection matrix
        PerspectiveProjectionMatrix projMat(30.0f, window.fbWidth(), window.fbHeight(), 1.0f, 1000.0f);

        //draw triangle test
        //glEnableVertexAttribArray(0);
        //glBindBuffer(GL_ARRAY_BUFFER, VAO);
        //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        //glBindVertexArray(VAO);

        //glUseProgram(program);
        vao->bind();
        vbo->setLayout(mesh.getLayout());
        std::vector<unsigned char> data = mesh.getVertexData();
        vbo->setData(data.size(), &data.front());
        ibo->bind();
        testMat.bind();
        tex1.bind(0);
        tex2.bind(1);
        //vbo->bindAttributeLocations(testMat);
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        vao->draw(6);
        testMat.unbind();
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
        ScaleMatrix scaleMat(scale);
        RotationMatrix2D rotMat(rot);
        TranslationMatrix transMat(pos);
        Mat4 MVP = projMat * transMat * rotMat * scaleMat;

        /*for(unsigned y = 0; y < 4; ++y) {
            std::cout << "| ";
            for(unsigned x = 0; x < 4; ++x) {
                std::cout << MVP.getVal(x, y) << " ";
            }
            std::cout << "|" << std::endl;
        }
        std::cout << "-----------------------------" << std::endl;*/

        testMat.setUniformMat4("MVP", MVP);

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

    return 0;
}
