#include <ostream>

namespace CrabEngine {
    namespace Math {

        typedef class Vec2 Vec2;
        typedef class Vec3 Vec3;

        class Vec4 {
        public:
            float x,y,z,w;
            float& r = x;
            float& g = y;
            float& b = z;
            float& a = w;

            float& red   = x;
            float& green = y;
            float& blue  = z;
            float& alpha = w;

            //constructors
            Vec4(float x, float y, float z, float w);
            Vec4(float v = 0);
            Vec4(const Vec4& other);
            Vec4(const Vec3& v3, float v = 0);
            Vec4(float v, const Vec3& v3);
            Vec4(const Vec2& v2, float z = 0, float w = 0);
            Vec4(float x, float y, const Vec2& v2);
            Vec4(float x, const Vec2& v2, float w = 0);
            Vec4(const Vec2& vec2_1, const Vec2& vec2_2);

            //Public Funcs
            float normalized();
            float magnitude();
            float magnitudeSquared();
            float distance(Vec4 other);
            float distanceSquared(Vec4 other);
            float dot(Vec4 other);
            Vec3 cross(Vec3 other);
            Vec4 midpoint(Vec2 other);
            Vec3 getHSV();
            void setHSV(Vec3 hsv);

            //Operators
            Vec4 operator+(const Vec4& other);
            Vec4 operator-(const Vec4& other);
            Vec4 operator*(const Vec4& other);
            Vec4 operator/(const Vec4& other);

            Vec4 operator+(const float& val);
            Vec4 operator-(const float& val);
            Vec4 operator*(const float& val);
            Vec4 operator/(const float& val);

            Vec4& operator+=(const Vec4& other);
            Vec4& operator-=(const Vec4& other);
            Vec4& operator*=(const Vec4& other);
            Vec4& operator/=(const Vec4& other);

            Vec4& operator+=(const float& val);
            Vec4& operator-=(const float& val);
            Vec4& operator*=(const float& val);
            Vec4& operator/=(const float& val);

            Vec4& operator=(const Vec4& other);
            Vec4& operator=(const float& val);

            Vec4 operator-();

            Vec4& operator++();
            Vec4& operator--();

            bool operator<(const Vec4& other);
            bool operator>(const Vec4& other);
            bool operator<=(const Vec4& other);
            bool operator>=(const Vec4& other);
            bool operator==(const Vec4& other);
            bool operator!=(const Vec4& other);


        };


        //non-member operators
        std::ostream& operator<<(std::ostream& os, const Vec4& vec);

    }
}
