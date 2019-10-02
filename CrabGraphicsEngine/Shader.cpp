#include "CrabShader.h"
#include <fstream>
#include <sstream>

namespace CrabEngine {
    namespace Graphics {


        //---------------
        // shader
        //---------------

        //window reset event callback
        void windowResetCallback(void* context) {
            ((Shader*)context)->Initialize();
        }

        //public functions

        Shader::Shader(Window& window, const std::string& path, GLuint shaderType) {
            //register with window reset callback
            windowInitEventCallback callback;
            callback.func = windowResetCallback;
            callback.context = (void*)this;
            window.registerInitFunc(callback);

            //set variables
            m_shaderType = shaderType;
            m_window = &window;

            //get shader source from file
            std::fstream file;
            file.open(path);
            std::stringstream sstr;
            sstr << file.rdbuf();
            m_shaderSource = sstr.str();

            //compile shader
            Initialize();
        }

        Shader::~Shader() {
            ((Window*)m_window)->removeInitFunc(this);

            glDeleteShader(m_shaderIndex);
        }

        GLuint Shader::getShaderID() const {
            return m_shaderIndex;
        }

        //private functions

        void Shader::Initialize() {
            //printf("Shader callback\n");
            const char* src = m_shaderSource.c_str();

            //create and compile shader
            m_shaderIndex = glCreateShader(m_shaderType);
            glShaderSource(m_shaderIndex, 1, &src, nullptr);
            glCompileShader(m_shaderIndex);

            //check shader for errors
            GLint Result = GL_FALSE;
            int InfoLogLength;

            glGetShaderiv(m_shaderIndex, GL_COMPILE_STATUS, &Result);
        	glGetShaderiv(m_shaderIndex, GL_INFO_LOG_LENGTH, &InfoLogLength);
        	if ( InfoLogLength > 0 ) {
        		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
        		glGetShaderInfoLog(m_shaderIndex, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        		printf("%s\n", &VertexShaderErrorMessage[0]);
        	}
        }

        //------------------
        // vertex shader
        //------------------

        //public functions

        VertexShader::VertexShader(Window& window, const std::string& path) :
            Shader(window, path, GL_VERTEX_SHADER) {}

        //------------------
        // fragment shader
        //------------------

        //public functions

        FragmentShader::FragmentShader(Window& window, const std::string& path) :
            Shader(window, path, GL_FRAGMENT_SHADER) {}

    }
}
