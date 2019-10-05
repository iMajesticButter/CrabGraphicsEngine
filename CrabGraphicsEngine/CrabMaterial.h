#ifndef CrabEngine_Graphics_Material_HEADER
#define CrabEngine_Graphics_Material_HEADER

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>

#include "CrabWindow.h"
#include "CrabShader.h"

namespace CrabEngine {
    namespace Graphics {

        class Material {
        public:

            Material(Window& window, const std::string name);
            ~Material();

            void AddShader(const Shader& shader);
            GLuint getProgram();
            void use();
            std::string getName();

            void Initialize();

            bool isInitialized();

            //set uniforms
            void setUniform1i  (const std::string name, const int val);
            void setUniform1ui (const std::string name, const unsigned val);
            void setUniform1f  (const std::string name, const float val);
            void setUniform1d  (const std::string name, const double val);

            void setUniform2i  (const std::string name, const int val1,      const int val2);
            void setUniform2ui (const std::string name, const unsigned val1, const unsigned val2);
            void setUniform2f  (const std::string name, const float val1,    const float val2);
            void setUniform2d  (const std::string name, const double val1,   const double val2);

            void setUniform3i  (const std::string name, const int val1,      const int val2,      const int val3);
            void setUniform3ui (const std::string name, const unsigned val1, const unsigned val2, const unsigned val3);
            void setUniform3f  (const std::string name, const float val1,    const float val2,    const float val3);
            void setUniform3d  (const std::string name, const double val1,   const double val2,   const double val3);

            void setUniform4i  (const std::string name, const int val1,      const int val2,      const int val3,      const int val4);
            void setUniform4ui (const std::string name, const unsigned val1, const unsigned val2, const unsigned val3, const unsigned val4);
            void setUniform4f  (const std::string name, const float val1,    const float val2,    const float val3,    const float val4);
            void setUniform4d  (const std::string name, const double val1,   const double val2,   const double val3,   const double val4);

        private:

            std::vector<Shader> m_shaders;

            Window* m_window;
            std::string m_name;

            GLuint m_program;
            bool m_initialized;

        };

    }
}

#endif
