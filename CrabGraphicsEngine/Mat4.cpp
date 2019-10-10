#include "CrabMat4.h"
#include "CrabVec2.h"
#include "CrabVec3.h"
#include "CrabVec4.h"

#define _USE_MATH_DEFINES
#include <math.h>

namespace CrabEngine {
    namespace Math {

        //-----------------------------------------
        // Local Functions
        //-----------------------------------------
        getIndex(unsigned x, unsigned y) {
            return (4*y)+x;
        }

        //-----------------------------------------
        // Mat4
        //-----------------------------------------

        //create identity matrix
        Mat4::Mat4() {
            for(int i = 0; i < 4*4; ++i) {
                m_mat[i] = 0;
            }

            m_mat[getIndex(0,0)] = 1;
            m_mat[getIndex(1,1)] = 1;
            m_mat[getIndex(2,2)] = 1;
            m_mat[getIndex(3,3)] = 1;
        }
        //copy constructor
        Mat4::Mat4(const Mat4& other) {
            for(int i = 0; i < 4*4; ++i) {
                m_mat[i] = other.m_mat[i];
            }
        }

        //getters
        float* Mat4::begin() {
            return m_mat;
        }
        float Mat4::getVal(unsigned x, unsigned y) const {
            return m_mat[getIndex(x,y)];
        }
        //setters
        void Mat4::setVal(float val, unsigned x, unsigned y) {
            m_mat[getIndex(x,y)] = val;
        }

        //operators
        Mat4 Mat4::operator*(const Mat4& other) {
            Mat4 mat;
            for(int i = 0; i < 4*4; ++i) {
                mat.m_mat[i] = 0;
            }
            for(int i = 0; i < 4; ++i) {
                for(int j = 0; j < 4; ++j) {
                    for(int x = 0; x < 4; ++x) {
                        mat.m_mat[getIndex(i,j)] += m_mat[getIndex(x,j)] * other.m_mat[getIndex(i,x)];
                    }
                }
            }
            return mat;
        }
        Mat4& Mat4::operator*=(const Mat4& other) {
            *this = *this * other;
            return *this;
        }
        Mat4& Mat4::operator=(const Mat4& other) {
            for(int i = 0; i < 4*4; ++i) {
                m_mat[i] = other.m_mat[i];
            }
            return *this;
        }

        //-----------------------------------------
        // TranslationMatrix
        //-----------------------------------------

        TranslationMatrix::TranslationMatrix(Vec4 pos) : Mat4() {
            m_mat[getIndex(3, 0)] = pos.x;
            m_mat[getIndex(3, 1)] = pos.y;
            m_mat[getIndex(3, 2)] = pos.z;
            m_mat[getIndex(3, 3)] = pos.w;
        }
        TranslationMatrix::TranslationMatrix(Vec3 pos) : Mat4() {
            m_mat[getIndex(3, 0)] = pos.x;
            m_mat[getIndex(3, 1)] = pos.y;
            m_mat[getIndex(3, 2)] = pos.z;
        }

        //-----------------------------------------
        // RotationMatrix2D
        //-----------------------------------------

        RotationMatrix2D::RotationMatrix2D(float radians) : Mat4() {
            m_mat[getIndex(0, 0)] = cos(radians);
            m_mat[getIndex(0, 1)] = -sin(radians);
            m_mat[getIndex(1, 0)] = sin(radians);
            m_mat[getIndex(1, 1)] = cos(radians);
        }

        //-----------------------------------------
        // ScaleMatrix
        //-----------------------------------------

        ScaleMatrix::ScaleMatrix(Vec2 scale) : Mat4() {
            m_mat[getIndex(0, 0)] = scale.x;
            m_mat[getIndex(1, 1)] = scale.y;
        }
        ScaleMatrix::ScaleMatrix(Vec3 scale) : Mat4() {
            m_mat[getIndex(0, 0)] = scale.x;
            m_mat[getIndex(1, 1)] = scale.y;
            m_mat[getIndex(2, 2)] = scale.z;
        }

        //-----------------------------------------
        // PerspectiveProjectionMatrix
        //-----------------------------------------

        PerspectiveProjectionMatrix::PerspectiveProjectionMatrix
        (float fov, unsigned viewportWidth, unsigned viewportHeight, float nearZ, float farZ) : Mat4() {
            float aspectRatio = (float)viewportWidth / (float)viewportHeight;
            float fovtan = tan((fov*(M_PI/180))/2);

            m_mat[getIndex(0,0)] = 1/(aspectRatio*fovtan);
            m_mat[getIndex(1,1)] = 1/fovtan;
            m_mat[getIndex(2,2)] = (-nearZ-farZ)/(nearZ-farZ);
            m_mat[getIndex(3,2)] = (2*farZ*nearZ)/(nearZ-farZ);
            m_mat[getIndex(2,3)] = 1;
            m_mat[getIndex(3,3)] = 0;

        }
    }
}
