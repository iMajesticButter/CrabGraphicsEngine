#include <ostream>

namespace CrabEngine {
    namespace Math {

        typedef class Vec3 Vec3;
        typedef class Vec4 Vec4;

        class Vec2 {
        public:
            float x,y;

            //constructors
            Vec2(float x, float y);
            Vec2(float v = 0);
            Vec2(const Vec2& other);
            Vec2(const Vec3& other);
            Vec2(const Vec4& other);

            //Public Funcs
            float normalized();
            float magnitude();
            float magnitudeSquared();
            float distance(Vec2 other);
            float distanceSquared(Vec2 other);
            float dot(Vec2 other);
            Vec3 cross(Vec3 other);
            Vec2 midpoint(Vec2 other);

            //Operators
            Vec2 operator+(const Vec2& other);
            Vec2 operator-(const Vec2& other);
            Vec2 operator*(const Vec2& other);
            Vec2 operator/(const Vec2& other);

            Vec2 operator+(const float& val);
            Vec2 operator-(const float& val);
            Vec2 operator*(const float& val);
            Vec2 operator/(const float& val);

            Vec2& operator+=(const Vec2& other);
            Vec2& operator-=(const Vec2& other);
            Vec2& operator*=(const Vec2& other);
            Vec2& operator/=(const Vec2& other);

            Vec2& operator+=(const float& val);
            Vec2& operator-=(const float& val);
            Vec2& operator*=(const float& val);
            Vec2& operator/=(const float& val);

            Vec2& operator=(const Vec2& other);
            Vec2& operator=(const float& val);

            Vec2 operator-();

            Vec2& operator++();
            Vec2& operator--();

            bool operator<(const Vec2& other);
            bool operator>(const Vec2& other);
            bool operator<=(const Vec2& other);
            bool operator>=(const Vec2& other);
            bool operator==(const Vec2& other);
            bool operator!=(const Vec2& other);


        };


        //non-member operators
        std::ostream& operator<<(std::ostream& os, const Vec2& vec);
    }
}
