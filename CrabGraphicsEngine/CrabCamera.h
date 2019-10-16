#ifndef CrabEngine_Graphics_Camera_HEADER
#define CrabEngine_Graphics_Camera_HEADER

#include "CrabVec2.h"
#include "CrabVec4.h"
#include "CrabMat4.h"

namespace CrabEngine {
    namespace Graphics {

        class Camera {
        public:

            CrabEngine::Math::Vec2 location;

            //! rotation in radians
            float rotation;
            //! perspective projection fov in degrees
            float fov;

            float size;
            bool active;

            //! larger = on top
            int renderLayer;

            Camera();

            CrabEngine::Math::Mat4 getTansformationMatrix();

            //! set the camera viewport
            /*!
              /param xPos the x position of the viewport from 0 to 1
              /param yPos the y position of the viewport from 0 to 1
              /param xScale the width of the viewport from 0 to 1
              /param yScale the height of the viewport from 0 to 1
            */
            void setViewportPos(float xPos, float yPos, float xScale, float yScale);

            //! get the viewport as a vec 4
            /*!
              /returns a Vec4 where the viewport xPos is x, yPos is y, xScale is z, and yScale is w
            */
            CrabEngine::Math::Vec4 getViewportAsVec4();

        private:

            CrabEngine::Math::Vec4 m_viewport;

        };

    }
}

#endif
