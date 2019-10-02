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
            Shader(Window& window, const std::string& path, GLuint shaderType);
            ~Shader();

            GLuint getShaderID() const;

            void Initialize();
        private:

            GLuint m_shaderIndex;
            GLuint m_shaderType;

            void* m_window;

            std::string m_shaderSource;

        };

        class VertexShader : public Shader {
        public:
            VertexShader(Window& window, const std::string& path);
        };

        class FragmentShader : public Shader {
        public:
            FragmentShader(Window& window, const std::string& path);
        };

    }
}

#endif
