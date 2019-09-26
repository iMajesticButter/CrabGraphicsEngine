#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

void glfwErrorCallback(int err, const char* description) {
    std::cerr << "ERROR: " << description << std::endl;
}


int main() {

    if(!glfwInit()) {
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
    glewInit();

    //triangle test

    static const char* vertex_shader_text =
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
    "}\n";

    //triangle
    const GLfloat gVertBufData[] = {
        0.0f,   1.0f,   0.0f,
        1.0f,  -1.0f,   0.0f,
       -1.0f,  -1.0f,   0.0f
    };

    GLuint VertArray;
    glGenVertexArrays(1, &VertArray);
    glBindVertexArray(VertArray);

    GLint Result = GL_FALSE;
	int InfoLogLength;

    //create vertex buffer
    GLuint vertexBuf;
    glGenBuffers(1, &vertexBuf);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(gVertBufData), gVertBufData, GL_STATIC_DRAW);

    GLuint VertShader = glCreateShader(GL_VERTEX_SHADER);
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
	}

    GLuint program = glCreateProgram();
    glAttachShader(program, VertShader);
    glAttachShader(program, FragShader);
    glLinkProgram(program);

    // Check the program
	glGetProgramiv(program, GL_LINK_STATUS, &Result);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(program, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

    glDetachShader(program, VertShader);
    glDetachShader(program, FragShader);

    glDeleteShader(VertShader);
    glDeleteShader(FragShader);

    while(!glfwWindowShouldClose(window)) {

        int width, height;

        glfwGetFramebufferSize(window, &width, &height);

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        //draw triangle test
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuf);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        glUseProgram(program);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);

        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        //printf("mouseY: %f\n", -(mouseY-height/2));

        GLint fragMousePos = glGetUniformLocation(program, "mousePos");
        if(fragMousePos != -1) {

            glUniform2f(fragMousePos, mouseX, -(mouseY-height));
        }

        glfwSwapBuffers(window);

        glfwPollEvents();

    }

    glfwDestroyWindow(window);

    glfwTerminate();

    return 0;
}
