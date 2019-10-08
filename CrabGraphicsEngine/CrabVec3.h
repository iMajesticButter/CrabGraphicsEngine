#include <ostream>

namespace CrabEngine {
    namespace Math {

        typedef class Vec2 Vec2;
        typedef class Vec4 Vec4;

        class Vec3 {
        public:
            float x,y,z;

            //constructors
            Vec3(float x, float y, float z);
            Vec3(float v = 0);
            Vec3(const Vec3& other);
            Vec3(const Vec2& v2, float v = 0);
            Vec3(float v, const Vec2& v2);
            Vec3(const Vec4& other);

            //Public Funcs
            Vec3 normalized() const;
            float magnitude() const;
            float magnitudeSquared() const;
            float distance(Vec3 other) const;
            float distanceSquared(Vec3 other) const;
            float dot(Vec3 other) const;
            Vec3 cross(Vec3 other) const;
            Vec3 midpoint(Vec3 other) const;

            //Operators
            Vec3 operator+(const Vec3& other) const;
            Vec3 operator-(const Vec3& other) const;
            Vec3 operator*(const Vec3& other) const;
            Vec3 operator/(const Vec3& other) const;

            Vec3 operator+(const float& val) const;
            Vec3 operator-(const float& val) const;
            Vec3 operator*(const float& val) const;
            Vec3 operator/(const float& val) const;

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

            Vec3 operator-() const;

            Vec3& operator++();
            Vec3& operator--();

            bool operator<(const Vec3& other) const;
            bool operator>(const Vec3& other) const;
            bool operator<=(const Vec3& other) const;
            bool operator>=(const Vec3& other) const;
            bool operator==(const Vec3& other) const;
            bool operator!=(const Vec3& other) const;
        };

        class hsv : public Vec3 {
        public:
            float& h = x;
            float& s = x;
            float& v = x;

            float& hue = x;
            float& saturation = x;
            float& value = x;
        };


        //non-member operators
        std::ostream& operator<<(std::ostream& os, const Vec3& vec);
    }
}
