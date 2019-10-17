#include "CrabTexture.h"
#include "CrabGraphicsUtils.h"

namespace CrabEngine {
    namespace Graphics {

        //---------------------------------------
        // Local Funcs
        //---------------------------------------
        void TextureInitEvent(void* context) {
            ((Texture*)context)->m_generated = false;
            if(((Texture*)context)->m_data.size() != 0) {
                ((Texture*)context)->Init();
            } else {
                ((Texture*)context)->Resize();
            }
        }

        //---------------------------------------
        // Public Funcs
        //---------------------------------------

        Texture::Texture(Window& window) : m_generated(false), m_window(&window), m_format(GL_RGBA), m_initialized(false), m_wrapMode(REPEAT), m_filterMode(NEAREST) {
        }
        Texture::~Texture() {
            if(m_initialized) {
                m_window->removeInitFunc(this);
            }
        }

        void Texture::setData(std::vector<unsigned char> data, unsigned width, unsigned height, GLenum format) {
            m_data = data;
            m_width = width;
            m_height = height;
            m_format = format;
        }
        void Texture::loadBitmap(const std::string& path) {
            textureData data = CrabEngine::Graphics::loadBitmap(path);
            m_data = data.data;
            m_width = data.width;
            m_height = data.height;
            m_format = GL_RGBA;
        }

        void Texture::setWrapMode(texWrapMode mode) {
            m_wrapMode = mode;
        }
        void Texture::setFilteringMode(texFilterMode mode) {
            m_filterMode = mode;
        }

        void Texture::setWidth(unsigned width) {
            m_width = width;
        }
        void Texture::setHeight(unsigned height) {
            m_height = height;
        }

        GLuint Texture::getTextureID() {
            return m_texture;
        }

        void Texture::bind(unsigned index) {
            glActiveTexture(GL_TEXTURE0 + index);
            glBindTexture(GL_TEXTURE_2D, m_texture);
        }

        void Texture::Init() {
            if(!m_initialized) {
                windowInitEventCallback callback;
                callback.context = this;
                callback.func = TextureInitEvent;

                m_window->registerInitFunc(callback);

                m_initialized = true;
            }
            if(!m_generated) {
                glGenTextures(1, &m_texture);
                m_generated = true;
            }
            glBindTexture(GL_TEXTURE_2D, m_texture);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrapMode);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrapMode);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filterMode);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filterMode);

            glTexImage2D(GL_TEXTURE_2D, 0, m_format, m_width, m_height, 0, m_format, GL_UNSIGNED_BYTE, &m_data.front());
            glGenerateMipmap(GL_TEXTURE_2D);

        }


        void Texture::Resize() {
            if(!m_initialized) {
                windowInitEventCallback callback;
                callback.context = this;
                callback.func = TextureInitEvent;

                m_window->registerInitFunc(callback);

                m_initialized = true;
            }
            if(!m_generated) {
                glGenTextures(1, &m_texture);
                m_generated = true;
            }

            m_data.clear();

            glBindTexture(GL_TEXTURE_2D, m_texture);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrapMode);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrapMode);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filterMode);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filterMode);

            glTexImage2D(GL_TEXTURE_2D, 0, m_format, m_width, m_height, 0, m_format, GL_UNSIGNED_BYTE, NULL);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
    }
}
