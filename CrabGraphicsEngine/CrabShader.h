#ifndef CrabEngine_Graphics_Shader_HEADER
#define CrabEngine_Graphics_Shader_HEADER

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <string>

#include "CrabWindow.h"


namespace CrabEngine {
    namespace Graphics {

        class Shader {
        public:
            Shader(const std::string& path, GLuint shaderType);
            Shader(const Shader& shader);

            std::string getSource();

            GLuint getType();

        private:
            GLuint m_shaderType;

            std::string m_shaderSource;
        };

        class VertexShader : public Shader {
        public:
            VertexShader(const std::string& path);
        };

        class FragmentShader : public Shader {
        public:
            FragmentShader(const std::string& path);
        };

    }
}

#endif
