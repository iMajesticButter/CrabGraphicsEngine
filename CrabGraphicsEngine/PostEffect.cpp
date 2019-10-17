#include "CrabPostEffect.h"

namespace CrabEngine {
    namespace Graphics {

        PostEffect::PostEffect() : active(true), m_mat(nullptr) {

        }
        PostEffect::PostEffect(Material* mat) : active(true), m_mat(mat) {

        }

        Material* PostEffect::getMaterial() {
            return m_mat;
        }
        void PostEffect::setMaterial(Material* mat) {
            m_mat = mat;
        }
    }
}
