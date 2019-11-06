#ifndef CrabEngine_Math_Mat4_HEADER
#define CrabEngine_Math_Mat4_HEADER

namespace CrabEngine {
    namespace Math {

        typedef class Vec2 Vec2;
        typedef class Vec3 Vec3;
        typedef class Vec4 Vec4;

        class Mat4 {
        public:
            //create identity matrix
            Mat4(bool initialize = true);
            //copy constructor
            Mat4(const Mat4& other);

            //getters
            const float* begin() const;
            float getVal(unsigned x, unsigned y) const;
            //setters
            void setVal(float val, unsigned x, unsigned y);

            //operators
            Mat4 operator*(const Mat4& other) const;
            Mat4& operator*=(const Mat4& other);
            Mat4& operator=(const Mat4& other);

            Vec4 operator*(const Vec4& other);
            Vec3 operator*(const Vec3& other);

        protected:
            //4x4 matrix data
            float m_mat[4*4];
        };

        class TranslationMatrix : public Mat4 {
        public:
            TranslationMatrix(Vec4 pos);
            TranslationMatrix(Vec3 pos);
        };

        class RotationMatrix2D : public Mat4 {
        public:
            RotationMatrix2D(float radians);
        };

        class ScaleMatrix : public Mat4 {
        public:
            ScaleMatrix(Vec2 scale);
            ScaleMatrix(Vec3 scale);
        };

        class PerspectiveProjectionMatrix : public Mat4 {
        public:
            PerspectiveProjectionMatrix(float fov, unsigned viewportWidth, unsigned viewportHeight, float nearZ, float farZ);
        };

    }
}
#endif
