#ifndef CrabEngine_Graphics_Texture_HEADER
#define CrabEngine_Graphics_Texture_HEADER

#include "GLEW/glew.h"

#include "CrabWindow.h"

#include <string>
#include <vector>

namespace CrabEngine {
    namespace Graphics {

        enum texWrapMode {
            REPEAT = GL_REPEAT,
            MIRRORED = GL_MIRRORED_REPEAT,
            CLAMP = GL_CLAMP_TO_EDGE,
            CLAMP_BORDER = GL_CLAMP_TO_BORDER
        };

        enum texFilterMode {
            LINEAR = GL_LINEAR,
            NEAREST = GL_NEAREST
        };

        class Texture {
        public:
            Texture(Window& window);
            ~Texture();

            void setData(std::vector<unsigned char> data, unsigned width, unsigned height, GLenum format);
            void loadBitmap(const std::string& path);

            void setWrapMode(texWrapMode mode);
            void setFilteringMode(texFilterMode mode);

            void setWidth(unsigned width);
            void setHeight(unsigned height);

            GLuint getTextureID();

            void bind(unsigned index);

            void Init();

            void Resize();

            bool m_generated;

            friend void TextureInitEvent(void* context);

        private:
            std::vector<unsigned char> m_data;
            Window* m_window;
            GLuint m_texture, m_width, m_height;
            GLenum m_format;
            bool m_initialized;

            texWrapMode m_wrapMode;
            texFilterMode m_filterMode;
        };

    }
}

#endif
