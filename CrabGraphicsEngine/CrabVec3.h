#include <ostream>

namespace CrabEngine {
    namespace Math {

        typedef class Vec2 Vec2;
        typedef class Vec4 Vec4;

        class Vec3 {
        public:
            float x,y,z;
            float& r = x;
            float& g = y;
            float& b = z;

            float& red   = x;
            float& green = y;
            float& blue  = z;

            //constructors
            Vec3(float x, float y, float z);
            Vec3(float v = 0);
            Vec3(const Vec3& other);
            Vec3(const Vec2& v2, float v = 0);
            Vec3(float v, const Vec2& v2);
            Vec3(const Vec4& other);

            //Public Funcs
            float normalized();
            float magnitude();
            float magnitudeSquared();
            float distance(Vec3 other);
            float distanceSquared(Vec3 other);
            float dot(Vec3 other);
            Vec3 cross(Vec3 other);
            Vec3 midpoint(Vec3 other);
            Vec3 getHSV();
            void setHSV(Vec3 hsv);
            Vec4 getColor();

            //Operators
            Vec3 operator+(const Vec3& other);
            Vec3 operator-(const Vec3& other);
            Vec3 operator*(const Vec3& other);
            Vec3 operator/(const Vec3& other);

            Vec3 operator+(const float& val);
            Vec3 operator-(const float& val);
            Vec3 operator*(const float& val);
            Vec3 operator/(const float& val);

            Vec3& operator+=(const Vec3& other);
            Vec3& operator-=(const Vec3& other);
            Vec3& operator*=(const Vec3& other);
            Vec3& operator/=(const Vec3& other);

            Vec3& operator+=(const float& val);
            Vec3& operator-=(const float& val);
            Vec3& operator*=(const float& val);
            Vec3& operator/=(const float& val);

            Vec3& operator=(const Vec3& other);
            Vec3& operator=(const float& val);

            Vec3 operator-();

            Vec3& operator++();
            Vec3& operator--();

            bool operator<(const Vec3& other);
            bool operator>(const Vec3& other);
            bool operator<=(const Vec3& other);
            bool operator>=(const Vec3& other);
            bool operator==(const Vec3& other);
            bool operator!=(const Vec3& other);
        };


        //non-member operators
        std::ostream& operator<<(std::ostream& os, const Vec3& vec);
    }
}
