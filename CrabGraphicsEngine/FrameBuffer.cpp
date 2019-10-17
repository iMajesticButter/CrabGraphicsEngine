#include "CrabFrameBuffer.h"
#include "CrabWindow.h"
#include "CrabTexture.h"

namespace CrabEngine {
    namespace Graphics {

        //----------------------------------------------------------
        // Local Funcs
        //----------------------------------------------------------

        void fbInitCallback(void* context) {
            ((FrameBuffer*)context)->Init();
        }

        //----------------------------------------------------------
        // Frame Buffer
        //----------------------------------------------------------

        FrameBuffer::FrameBuffer(Window* window) : m_window(window) {
            windowInitEventCallback callback;
            callback.context  = this;
            callback.func = fbInitCallback;
            m_window->registerInitFunc(callback);

            Init();

        }
        FrameBuffer::~FrameBuffer() {
            m_window->removeInitFunc(this);
        }

        void FrameBuffer::Init() {
            m_width = m_window->fbWidth();
            m_height = m_window->fbHeight();

            //create the render bufffers (depth and stencil buffers)
            glGenRenderbuffers(1, &m_rbo);
            glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width, m_height);
            glBindRenderbuffer(GL_RENDERBUFFER, 0);

            glGenFramebuffers(1, &m_fbo);
            bind();
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);
            unbind();
        }

        void FrameBuffer::setTexture(Texture* tex) {
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex->getTextureID(), 0);
        }

        void FrameBuffer::resize(unsigned width, unsigned height) {
            if(m_width == width && m_height == height) {
                return;
            }
            m_width = width;
            m_height = height;
            glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width, m_height);
            glBindRenderbuffer(GL_RENDERBUFFER, 0);
        }

        void FrameBuffer::bind() {
            glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
        }
        void FrameBuffer::unbind() {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }
    }
}
