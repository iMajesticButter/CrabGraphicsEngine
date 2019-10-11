#ifndef CrabEngine_Graphics_VBO_HEADER
#define CrabEngine_Graphics_VBO_HEADER

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include "CrabWindow.h"

#include <vector>
#include <string>

namespace CrabEngine {
    namespace Graphics {
        enum VBOusage {
            STATIC,
            DYNAMIC
        };

        typedef class VBO VBO;

        struct VBOattribute {
            GLenum type;
            GLuint count;
            GLboolean normalized;
            GLuint offset;
            GLuint location;
            std::string name;
        };

        class VBOlayout {
        public:
            VBOlayout();
            VBOlayout(const VBOlayout& other);
            VBOlayout(GLuint stride);

            void addAttribute(std::string name, GLenum type, GLuint count, GLuint size, GLboolean normalized = GL_FALSE);
            void clearAttributes();

            friend VBO;
        private:
            std::vector<VBOattribute> m_attributes;
            GLuint m_stride;
            GLuint m_index;
            unsigned m_count;
        };

        class VBO {
        public:
            VBO(VBOusage usage);
            ~VBO();

            void resize(unsigned size);
            void setLayout(const VBOlayout& layout);
            void setData(const unsigned size, const void* data);
            void* getPointerInternal();
            void releasePointer();
            void bind();
            void unbind();

        private:
            VBOusage m_usage;
            GLuint m_vbo;
            unsigned m_size;
            VBOlayout m_layout;
            Window* m_window;
        };
    }
}

#endif
