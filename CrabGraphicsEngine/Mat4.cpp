#include "CrabMat4.h"
#include "CrabVec2.h"
#include "CrabVec3.h"
#include "CrabVec4.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <cstring>

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
        Mat4::Mat4(bool initialize) {
            //for(int i = 0; i < 4*4; ++i) {
            //    m_mat[i] = 0;
            //}

            if(!initialize)
                return;

            memset(m_mat, 0, sizeof(float) * (4*4));

            m_mat[0] = 1;
            m_mat[5] = 1;
            m_mat[10] = 1;
            m_mat[15] = 1;
        }
        //copy constructor
        Mat4::Mat4(const Mat4& other) {
            //for(int i = 0; i < 4*4; ++i) {
            //    m_mat[i] = other.m_mat[i];
            //}
            memcpy(m_mat, other.m_mat, sizeof(float) * (4*4));
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
            Mat4 mat(false);
            /*for(unsigned i = 0; i < 4; ++i) {
                for(unsigned j = 0; j < 4; ++j) {
                    //for(int x = 0; x < 4; ++x) {
                    //    mat.m_mat[getIndex(i,j)] += m_mat[getIndex(x,j)] * other.m_mat[getIndex(i,x)];
                    //}
                    mat.m_mat[getIndex(i,j)] = m_mat[getIndex(0,j)] * other.m_mat[getIndex(i,0)]
                                             + m_mat[getIndex(1,j)] * other.m_mat[getIndex(i,1)]
                                             + m_mat[getIndex(2,j)] * other.m_mat[getIndex(i,2)]
                                             + m_mat[getIndex(3,j)] * other.m_mat[getIndex(i,3)];
                }
            }*/

            mat.m_mat[0] = m_mat[0] * other.m_mat[0] +   m_mat[1] * other.m_mat[4] +   m_mat[2] * other.m_mat[8] + m_mat[3] * other.m_mat[12];
            mat.m_mat[1] = m_mat[0] * other.m_mat[1] +   m_mat[1] * other.m_mat[5] +   m_mat[2] * other.m_mat[9] + m_mat[3] * other.m_mat[13];
            mat.m_mat[2] = m_mat[0] * other.m_mat[2] +   m_mat[1] * other.m_mat[6] +   m_mat[2] * other.m_mat[10] + m_mat[3] * other.m_mat[14];
            mat.m_mat[3] = m_mat[0] * other.m_mat[3] +   m_mat[1] * other.m_mat[7] +   m_mat[2] * other.m_mat[11] + m_mat[3] * other.m_mat[15];

            mat.m_mat[4] = m_mat[4] * other.m_mat[0] +   m_mat[5] * other.m_mat[4] +   m_mat[6] * other.m_mat[8] + m_mat[7] * other.m_mat[12];
            mat.m_mat[5] = m_mat[4] * other.m_mat[1] +   m_mat[5] * other.m_mat[5] +   m_mat[6] * other.m_mat[9] + m_mat[7] * other.m_mat[13];
            mat.m_mat[6] = m_mat[4] * other.m_mat[2] +   m_mat[5] * other.m_mat[6] +   m_mat[6] * other.m_mat[10] + m_mat[7] * other.m_mat[14];
            mat.m_mat[7] = m_mat[4] * other.m_mat[3] +   m_mat[5] * other.m_mat[7] +   m_mat[6] * other.m_mat[11] + m_mat[7] * other.m_mat[15];

            mat.m_mat[8] = m_mat[8] * other.m_mat[0] +   m_mat[9] * other.m_mat[4] +   m_mat[10] * other.m_mat[8] + m_mat[11] * other.m_mat[12];
            mat.m_mat[9] = m_mat[8] * other.m_mat[1] +   m_mat[9] * other.m_mat[5] +   m_mat[10] * other.m_mat[9] + m_mat[11] * other.m_mat[13];
            mat.m_mat[10] = m_mat[8] * other.m_mat[2] +   m_mat[9] * other.m_mat[6] +   m_mat[10] * other.m_mat[10] + m_mat[11] * other.m_mat[14];
            mat.m_mat[11] = m_mat[8] * other.m_mat[3] +   m_mat[9] * other.m_mat[7] +   m_mat[10] * other.m_mat[11] + m_mat[11] * other.m_mat[15];

            mat.m_mat[12] = m_mat[12] * other.m_mat[0] +   m_mat[13] * other.m_mat[4] +   m_mat[14] * other.m_mat[8] + m_mat[15] * other.m_mat[12];
            mat.m_mat[13] = m_mat[12] * other.m_mat[1] +   m_mat[13] * other.m_mat[5] +   m_mat[14] * other.m_mat[9] + m_mat[15] * other.m_mat[13];
            mat.m_mat[14] = m_mat[12] * other.m_mat[2] +   m_mat[13] * other.m_mat[6] +   m_mat[14] * other.m_mat[10] + m_mat[15] * other.m_mat[14];
            mat.m_mat[15] = m_mat[12] * other.m_mat[3] +   m_mat[13] * other.m_mat[7] +   m_mat[14] * other.m_mat[11] + m_mat[15] * other.m_mat[15];


            return mat;
        }
        Mat4& Mat4::operator*=(const Mat4& other) {
            *this = *this * other;
            return *this;
        }
        Mat4& Mat4::operator=(const Mat4& other) {
            //for(int i = 0; i < 4*4; ++i) {
            //    m_mat[i] = other.m_mat[i];
            //}
            memcpy(m_mat, other.m_mat, sizeof(float) * (4*4));
            return *this;
        }

        Vec4 Mat4::operator*(const Vec4& other) {
            Vec4 out;
            out.x = m_mat[getIndex(0,0)]*other.x + m_mat[getIndex(1,0)]*other.y + m_mat[getIndex(2,0)]*other.z + m_mat[getIndex(3,0)]*other.w;
            out.y = m_mat[getIndex(0,1)]*other.x + m_mat[getIndex(1,1)]*other.y + m_mat[getIndex(2,1)]*other.z + m_mat[getIndex(3,1)]*other.w;
            out.z = m_mat[getIndex(0,2)]*other.x + m_mat[getIndex(1,2)]*other.y + m_mat[getIndex(2,2)]*other.z + m_mat[getIndex(3,2)]*other.w;
            out.w = m_mat[getIndex(0,3)]*other.x + m_mat[getIndex(1,3)]*other.y + m_mat[getIndex(2,3)]*other.z + m_mat[getIndex(3,3)]*other.w;
            return out;
        }

        Vec3 Mat4::operator*(const Vec3& other) {
            Vec3 out;
            out.x = m_mat[getIndex(0,0)]*other.x + m_mat[getIndex(1,0)]*other.y + m_mat[getIndex(2,0)]*other.z + m_mat[getIndex(3,0)];
            out.y = m_mat[getIndex(0,1)]*other.x + m_mat[getIndex(1,1)]*other.y + m_mat[getIndex(2,1)]*other.z + m_mat[getIndex(3,1)];
            out.z = m_mat[getIndex(0,2)]*other.x + m_mat[getIndex(1,2)]*other.y + m_mat[getIndex(2,2)]*other.z + m_mat[getIndex(3,2)];
            return out;
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
