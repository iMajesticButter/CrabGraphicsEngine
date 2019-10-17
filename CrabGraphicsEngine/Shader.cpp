#include "CrabShader.h"
#include <fstream>
#include <sstream>
#include <iostream>

namespace CrabEngine {
    namespace Graphics {


        //---------------
        // shader
        //---------------

        //public functions

        Shader::Shader(const std::string& path, GLuint shaderType) {
            //set variables
            m_shaderType = shaderType;

            //get shader source from file
            std::fstream file;
            file.open(path);
            if(!file) {
                std::cout << "Shader File: " << path << " Does Not Exist!!" << std::endl;
                m_shaderSource = "";
                return;
            }
            std::stringstream sstr;
            sstr << file.rdbuf();
            m_shaderSource = sstr.str();
            file.close();
        }

        Shader::Shader(const Shader& shader) {
            m_shaderType = shader.m_shaderType;
            m_shaderSource = shader.m_shaderSource;
        }

        std::string& Shader::getSource() {
            return m_shaderSource;
        }

        GLuint Shader::getType() {
            return m_shaderType;
        }

        //------------------
        // vertex shader
        //------------------

        //public functions

        VertexShader::VertexShader(const std::string& path) :
            Shader(path, GL_VERTEX_SHADER) {}

        //------------------
        // fragment shader
        //------------------

        //public functions

        FragmentShader::FragmentShader(const std::string& path) :
            Shader(path, GL_FRAGMENT_SHADER) {}

    }
}
