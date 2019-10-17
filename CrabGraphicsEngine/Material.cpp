#include "CrabMaterial.h"

namespace CrabEngine {
    namespace Graphics {

        //Window reset event
        void windowReset(void* context) {
            if(((Material*)context)->isInitialized()) {
                ((Material*)context)->Initialize();
            }
        }

        //-------------------------
        // Public Funcs
        //-------------------------

        Material::Material(Window& window, const std::string name) : m_initialized(false), m_bound(false) {
            m_name = name;
            m_window = &window;

            //register initialize function on window reset event
            windowInitEventCallback windowResetCallback;
            windowResetCallback.func = windowReset;
            windowResetCallback.context = this;
            m_window->registerInitFunc(windowResetCallback);

        }

        Material::~Material() {
            if(m_initialized) {
                glDeleteProgram(m_program);
            }
            m_window->removeInitFunc(this);
        }

        void Material::AddShader(const Shader& shader) {
            m_shaders.push_back(shader);
        }
        GLuint Material::getProgram() {
            if(m_initialized) {
                return m_program;
            }
            return 0;
        }
        void Material::bind() {
            if(m_initialized) {
                glUseProgram(m_program);
                m_bound = true;
            }
        }
        void Material::unbind() {
            glUseProgram(0);
            m_bound = false;
        }
        std::string Material::getName() {
            return m_name;
        }

        void Material::Initialize() {
            //error vars
            GLint Result = GL_FALSE;
            int InfoLogLength;

            //compile the shaders
            std::vector<GLuint> shaders;
            for(unsigned i = 0; i < m_shaders.size(); ++i) {

                //compile shader
                const char* src = m_shaders[i].getSource().c_str();

                shaders.push_back(glCreateShader(m_shaders[i].getType()));
                glShaderSource(shaders[i], 1, &src, nullptr);
                glCompileShader(shaders[i]);

                //check Shader for Errors
            	glGetShaderiv(shaders[i], GL_COMPILE_STATUS, &Result);
            	glGetShaderiv(shaders[i], GL_INFO_LOG_LENGTH, &InfoLogLength);
            	if ( InfoLogLength > 0 ){
            		std::vector<char> ShaderErrorMessage(InfoLogLength+1);
            		glGetShaderInfoLog(shaders[i], InfoLogLength, NULL, &ShaderErrorMessage[0]);
                    printf("Shader Error:\n");
            		printf("%s\n", &ShaderErrorMessage[0]);
                    printf("Source: %s\n", src);
            	}
            }

            //delete old program
            if(m_initialized) {
                glDeleteProgram(m_program);
            }

            //create a new program
            m_program = glCreateProgram();

            //set program shaders
            for(unsigned i = 0; i < shaders.size(); ++i) {
                glAttachShader(m_program, shaders[i]);
            }

            //attribute locations
            glBindAttribLocation(m_program, 0, "in_Position");
            //glBindAttribLocation(m_program, 1, "in_Color");
            glBindAttribLocation(m_program, 1, "in_UV");

            //link Program
            glLinkProgram(m_program);

            //check program for errors
        	glGetProgramiv(m_program, GL_LINK_STATUS, &Result);
        	glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &InfoLogLength);
        	if ( InfoLogLength > 0 ){
        		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
        		glGetProgramInfoLog(m_program, InfoLogLength, NULL, &ProgramErrorMessage[0]);
                printf("Shader Program Error:\n");
        		printf("%s\n", &ProgramErrorMessage[0]);
                printf("Source: %s\n", m_name.c_str());
        	}

            //detach and delete shaders
            for(unsigned i = 0; i < shaders.size(); ++i) {
                glDetachShader(m_program, shaders[i]);
                glDeleteShader(shaders[i]);
            }

            m_initialized = true;

        }

        bool Material::isInitialized() {
            return m_initialized;
        }


        //-----------------------------
        // Set Uniforms
        //-----------------------------


        void Material::setUniform1i  (const std::string name, const int val) {
            if(!m_bound)
                glUseProgram(m_program);
            GLint uniformPointer = glGetUniformLocation(m_program, name.c_str());
            if(uniformPointer != -1) {
                glUniform1i(uniformPointer, val);
            }
            if(!m_bound)
                glUseProgram(0);
        }
        void Material::setUniform1ui (const std::string name, const unsigned val) {
            if(!m_bound)
                glUseProgram(m_program);
            GLint uniformPointer = glGetUniformLocation(m_program, name.c_str());
            if(uniformPointer != -1) {
                glUniform1ui(uniformPointer, val);
            }
            if(!m_bound)
                glUseProgram(0);
        }
        void Material::setUniform1f  (const std::string name, const float val) {
            if(!m_bound)
                glUseProgram(m_program);
            GLint uniformPointer = glGetUniformLocation(m_program, name.c_str());
            if(uniformPointer != -1) {
                glUniform1f(uniformPointer, val);
            }
            if(!m_bound)
                glUseProgram(0);
        }
        void Material::setUniform1d  (const std::string name, const double val) {
            if(!m_bound)
                glUseProgram(m_program);
            GLint uniformPointer = glGetUniformLocation(m_program, name.c_str());
            if(uniformPointer != -1) {
                glUniform1d(uniformPointer, val);
            }
            if(!m_bound)
                glUseProgram(0);
        }


        void Material::setUniform2i  (const std::string name, const int val1,      const int val2) {
            if(!m_bound)
                glUseProgram(m_program);
            GLint uniformPointer = glGetUniformLocation(m_program, name.c_str());
            if(uniformPointer != -1) {
                glUniform2i(uniformPointer, val1, val2);
            }
            if(!m_bound)
                glUseProgram(0);
        }
        void Material::setUniform2ui (const std::string name, const unsigned val1, const unsigned val2) {
            if(!m_bound)
                glUseProgram(m_program);
            GLint uniformPointer = glGetUniformLocation(m_program, name.c_str());
            if(uniformPointer != -1) {
                glUniform2ui(uniformPointer, val1, val2);
            }
            if(!m_bound)
                glUseProgram(0);
        }
        void Material::setUniform2f  (const std::string name, const float val1,    const float val2) {
            if(!m_bound)
                glUseProgram(m_program);
            GLint uniformPointer = glGetUniformLocation(m_program, name.c_str());
            if(uniformPointer != -1) {
                glUniform2f(uniformPointer, val1, val2);
            }
            if(!m_bound)
                glUseProgram(0);
        }
        void Material::setUniform2d  (const std::string name, const double val1,   const double val2) {
            if(!m_bound)
                glUseProgram(m_program);
            GLint uniformPointer = glGetUniformLocation(m_program, name.c_str());
            if(uniformPointer != -1) {
                glUniform2d(uniformPointer, val1, val2);
            }
            if(!m_bound)
                glUseProgram(0);
        }

        void Material::setUniform3i  (const std::string name, const int val1,      const int val2,      const int val3) {
            if(!m_bound)
                glUseProgram(m_program);
            GLint uniformPointer = glGetUniformLocation(m_program, name.c_str());
            if(uniformPointer != -1) {
                glUniform3i(uniformPointer, val1, val2, val3);
            }
            if(!m_bound)
                glUseProgram(0);
        }
        void Material::setUniform3ui (const std::string name, const unsigned val1, const unsigned val2, const unsigned val3) {
            if(!m_bound)
                glUseProgram(m_program);
            GLint uniformPointer = glGetUniformLocation(m_program, name.c_str());
            if(uniformPointer != -1) {
                glUniform3ui(uniformPointer, val1, val2, val3);
            }
            if(!m_bound)
                glUseProgram(0);
        }
        void Material::setUniform3f  (const std::string name, const float val1,    const float val2,    const float val3) {
            if(!m_bound)
                glUseProgram(m_program);
            GLint uniformPointer = glGetUniformLocation(m_program, name.c_str());
            if(uniformPointer != -1) {
                glUniform3f(uniformPointer, val1, val2, val3);
            }
            if(!m_bound)
                glUseProgram(0);
        }
        void Material::setUniform3d  (const std::string name, const double val1,   const double val2,   const double val3) {
            if(!m_bound)
                glUseProgram(m_program);
            GLint uniformPointer = glGetUniformLocation(m_program, name.c_str());
            if(uniformPointer != -1) {
                glUniform3d(uniformPointer, val1, val2, val3);
            }
            if(!m_bound)
                glUseProgram(0);
        }

        void Material::setUniform4i  (const std::string name, const int val1,      const int val2,      const int val3,      const int val4) {
            if(!m_bound)
                glUseProgram(m_program);
            GLint uniformPointer = glGetUniformLocation(m_program, name.c_str());
            if(uniformPointer != -1) {
                glUniform4i(uniformPointer, val1, val2, val3, val4);
            }
            if(!m_bound)
                glUseProgram(0);
        }
        void Material::setUniform4ui (const std::string name, const unsigned val1, const unsigned val2, const unsigned val3, const unsigned val4) {
            if(!m_bound)
                glUseProgram(m_program);
            GLint uniformPointer = glGetUniformLocation(m_program, name.c_str());
            if(uniformPointer != -1) {
                glUniform4ui(uniformPointer, val1, val2, val3, val4);
            }
            if(!m_bound)
                glUseProgram(0);
        }
        void Material::setUniform4f  (const std::string name, const float val1,    const float val2,    const float val3,    const float val4) {
            if(!m_bound)
                glUseProgram(m_program);
            GLint uniformPointer = glGetUniformLocation(m_program, name.c_str());
            if(uniformPointer != -1) {
                glUniform4f(uniformPointer, val1, val2, val3, val4);
            }
            if(!m_bound)
                glUseProgram(0);
        }
        void Material::setUniform4d  (const std::string name, const double val1,   const double val2,   const double val3,   const double val4) {
            if(!m_bound)
                glUseProgram(m_program);
            GLint uniformPointer = glGetUniformLocation(m_program, name.c_str());
            if(uniformPointer != -1) {
                glUniform4d(uniformPointer, val1, val2, val3, val4);
            }
            if(!m_bound)
                glUseProgram(0);
        }

        void Material::setUniform2f  (const std::string name, const CrabEngine::Math::Vec2& vec) {
            if(!m_bound)
                glUseProgram(m_program);
            GLint uniformPointer = glGetUniformLocation(m_program, name.c_str());
            if(uniformPointer != -1) {
                glUniform2f(uniformPointer, vec.x, vec.y);
            }
            if(!m_bound)
                glUseProgram(0);
        }
        void Material::setUniform3f  (const std::string name, const CrabEngine::Math::Vec3& vec) {
            if(!m_bound)
                glUseProgram(m_program);
            GLint uniformPointer = glGetUniformLocation(m_program, name.c_str());
            if(uniformPointer != -1) {
                glUniform3f(uniformPointer, vec.x, vec.y, vec.z);
            }
            if(!m_bound)
                glUseProgram(0);
        }
        void Material::setUniform4f  (const std::string name, const CrabEngine::Math::Vec4& vec) {
            if(!m_bound)
                glUseProgram(m_program);
            GLint uniformPointer = glGetUniformLocation(m_program, name.c_str());
            if(uniformPointer != -1) {
                glUniform4f(uniformPointer, vec.x, vec.y, vec.z, vec.w);
            }
            if(!m_bound)
                glUseProgram(0);
        }

        void Material::setUniformMat4(const std::string name, CrabEngine::Math::Mat4& mat) {
            if(!m_bound)
                glUseProgram(m_program);
            GLint uniformPointer = glGetUniformLocation(m_program, name.c_str());
            if(uniformPointer != -1) {
                glUniformMatrix4fv(uniformPointer, 1, GL_TRUE, mat.begin());
            }
            if(!m_bound)
                glUseProgram(0);
        }

    }
}
