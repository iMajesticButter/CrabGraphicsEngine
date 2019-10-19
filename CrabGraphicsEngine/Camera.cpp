#include "CrabCamera.h"
#include <math.h>

namespace CrabEngine {
    namespace Graphics {

        Camera::Camera() : location(0,0), rotation(0), fov(30.0f), size(1), active(true), clearColor(0,0,0,255), renderLayer(0), m_viewport(0,0,1,1) {

        }

        CrabEngine::Math::Mat4 Camera::getTansformationMatrix() {
            using namespace CrabEngine::Math;
            if(size <= 0)
                size = 0.0001f;
            float scale = 1/size;
            ScaleMatrix scaleMat(Vec2(scale, scale));
            RotationMatrix2D rotMat(-rotation);
            TranslationMatrix transMat(Vec4(-location, 10.0f, 1.0f));
            return transMat * rotMat * scaleMat;
        }

        // set the camera viewport
        void Camera::setViewportPos(float xPos, float yPos, float xScale, float yScale) {
            m_viewport = CrabEngine::Math::Vec4(xPos, yPos, xScale, yScale);
        }

        // get the viewport as a vec 4
        CrabEngine::Math::Vec4 Camera::getViewportAsVec4() {
            return m_viewport;
        }


        void Camera::addPostEffect(PostEffect* effect) {
            m_postEffects.push_back(effect);
        }
        std::vector<PostEffect*> Camera::getPostEffects() {
            return m_postEffects;
        }
        void Camera::removePostEffect(unsigned index) {
            if(index < m_postEffects.size()) {
                m_postEffects.erase(m_postEffects.begin()+index);
            }
        }
        void Camera::removePostEffect(PostEffect* effect) {
            for(unsigned i = 0; i < m_postEffects.size(); ++i) {
                if(m_postEffects[i] == effect) {
                    removePostEffect(i);
                    return;
                }
            }
        }
    }
}
