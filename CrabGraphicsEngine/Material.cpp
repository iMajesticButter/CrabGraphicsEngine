#include "CrabMaterial.h"


namespace CrabEngine {
    namespace Graphics {

        Material::Material(Window& window, const std::string name) : m_initialized(false) {
            m_name = name;
            m_window = &window;
        }

        Material::~Material() {
            if(m_initialized) {
                glDeleteProgram(m_program);
            }
        }

        void Material::AddShader(const Shader& shader) {
            m_shaders.push_back(shader);
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
            		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
            		glGetShaderInfoLog(shaders[i], InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
            		printf("%s\n", &VertexShaderErrorMessage[0]);
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

            //link Program
            glLinkProgram(m_program);

            //check program for errors
        	glGetProgramiv(m_program, GL_LINK_STATUS, &Result);
        	glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &InfoLogLength);
        	if ( InfoLogLength > 0 ){
        		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
        		glGetProgramInfoLog(m_program, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        		printf("%s\n", &ProgramErrorMessage[0]);
        	}

            //detach and delete shaders
            for(unsigned i = 0; i < shaders.size(); ++i) {
                glDetachShader(m_program, shaders[i]);
                glDeleteShader(shaders[i]);
            }
        }


        //-----------------------------
        // Set Uniforms
        //-----------------------------


        void Material::setUniform1i  (const std::string name, const int val) {
            GLint uniformPointer = glGetUniformLocation(m_program, name.c_str());
            if(uniformPointer != -1) {
                glUniform1i(uniformPointer, val);
            }
        }
        void Material::setUniform1ui (const std::string name, const unsigned val) {
            GLint uniformPointer = glGetUniformLocation(m_program, name.c_str());
            if(uniformPointer != -1) {
                glUniform1ui(uniformPointer, val);
            }
        }
        void Material::setUniform1f  (const std::string name, const float val) {
            GLint uniformPointer = glGetUniformLocation(m_program, name.c_str());
            if(uniformPointer != -1) {
                glUniform1f(uniformPointer, val);
            }
        }
        void Material::setUniform1d  (const std::string name, const double val) {
            GLint uniformPointer = glGetUniformLocation(m_program, name.c_str());
            if(uniformPointer != -1) {
                glUniform1d(uniformPointer, val);
            }
        }


        void Material::setUniform2i  (const std::string name, const int val1,      const int val2) {
            GLint uniformPointer = glGetUniformLocation(m_program, name.c_str());
            if(uniformPointer != -1) {
                glUniform2i(uniformPointer, val1, val2);
            }
        }
        void Material::setUniform2ui (const std::string name, const unsigned val1, const unsigned val2) {
            GLint uniformPointer = glGetUniformLocation(m_program, name.c_str());
            if(uniformPointer != -1) {
                glUniform2ui(uniformPointer, val1, val2);
            }
        }
        void Material::setUniform2f  (const std::string name, const float val1,    const float val2) {
            GLint uniformPointer = glGetUniformLocation(m_program, name.c_str());
            if(uniformPointer != -1) {
                glUniform2f(uniformPointer, val1, val2);
            }
        }
        void Material::setUniform2d  (const std::string name, const double val1,   const double val2) {
            GLint uniformPointer = glGetUniformLocation(m_program, name.c_str());
            if(uniformPointer != -1) {
                glUniform2d(uniformPointer, val1, val2);
            }
        }

        void Material::setUniform3i  (const std::string name, const int val1,      const int val2,      const int val3) {
            GLint uniformPointer = glGetUniformLocation(m_program, name.c_str());
            if(uniformPointer != -1) {
                glUniform3i(uniformPointer, val1, val2, val3);
            }
        }
        void Material::setUniform3ui (const std::string name, const unsigned val1, const unsigned val2, const unsigned val3) {
            GLint uniformPointer = glGetUniformLocation(m_program, name.c_str());
            if(uniformPointer != -1) {
                glUniform3ui(uniformPointer, val1, val2, val3);
            }
        }
        void Material::setUniform3f  (const std::string name, const float val1,    const float val2,    const float val3) {
            GLint uniformPointer = glGetUniformLocation(m_program, name.c_str());
            if(uniformPointer != -1) {
                glUniform3f(uniformPointer, val1, val2, val3);
            }
        }
        void Material::setUniform3d  (const std::string name, const double val1,   const double val2,   const double val3) {
            GLint uniformPointer = glGetUniformLocation(m_program, name.c_str());
            if(uniformPointer != -1) {
                glUniform3d(uniformPointer, val1, val2, val3);
            }
        }

        void Material::setUniform4i  (const std::string name, const int val1,      const int val2,      const int val3,      const int val4) {
            GLint uniformPointer = glGetUniformLocation(m_program, name.c_str());
            if(uniformPointer != -1) {
                glUniform4i(uniformPointer, val1, val2, val3, val4);
            }
        }
        void Material::setUniform4ui (const std::string name, const unsigned val1, const unsigned val2, const unsigned val3, const unsigned val4) {
            GLint uniformPointer = glGetUniformLocation(m_program, name.c_str());
            if(uniformPointer != -1) {
                glUniform4ui(uniformPointer, val1, val2, val3, val4);
            }
        }
        void Material::setUniform4f  (const std::string name, const float val1,    const float val2,    const float val3,    const float val4) {
            GLint uniformPointer = glGetUniformLocation(m_program, name.c_str());
            if(uniformPointer != -1) {
                glUniform4f(uniformPointer, val1, val2, val3, val4);
            }
        }
        void Material::setUniform4d  (const std::string name, const double val1,   const double val2,   const double val3,   const double val4) {
            GLint uniformPointer = glGetUniformLocation(m_program, name.c_str());
            if(uniformPointer != -1) {
                glUniform4d(uniformPointer, val1, val2, val3, val4);
            }
        }
    }
}
