#ifndef CrabEngine_Graphics_Renderer2D_HEADER
#define CrabEngine_Graphics_Renderer2D_HEADER

#include "CrabWindow.h"
//#include "CrabVAO.h"
//#include "CrabVBO.h"
//#include "CrabIBO.h"
//#include "CrabGraphicsObject2D.h"


#include <vector>

#define byte unsigned char

namespace CrabEngine {
    namespace Graphics {

        typedef class VAO VAO;
        typedef class VBO VBO;
        typedef class IBO IBO;
        typedef class GraphicsObject2D GraphicsObject2D;
        typedef class Camera Camera;


        class Renderer2D {
        public:

            Renderer2D(Window* window);
            ~Renderer2D();

            void Init();

            void start();
            void pushCamera(Camera* cam);
            void pushObject(GraphicsObject2D* obj);
            void end();

        private:

            Window* m_window;

            std::vector<GraphicsObject2D*> m_objects;
            std::vector<Camera*> m_cams;

            VAO* m_vao = nullptr;
            VBO* m_vbo = nullptr;
            IBO* m_ibo = nullptr;

            bool m_active = false;

            unsigned m_numVertecies;
            unsigned m_numIndecies;

            //std::vector<byte> m_vertecies;
            //std::vector<unsigned> m_triangles;

            //unsigned m_triOffset;
        };
    }
}

#endif
