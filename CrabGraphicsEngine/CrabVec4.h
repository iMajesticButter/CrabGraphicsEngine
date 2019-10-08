#include <ostream>

namespace CrabEngine {
    namespace Math {

        typedef class Vec2 Vec2;
        typedef class Vec3 Vec3;
        typedef class hsv hsv;

        class Vec4 {
        public:
            float x,y,z,w;

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
            Vec4 normalized() const;
            float magnitude() const;
            float magnitudeSquared() const;
            float distance(Vec4 other) const;
            float distanceSquared(Vec4 other) const;
            float dot(Vec4 other) const;
            Vec3 cross(Vec3 other) const;
            Vec4 midpoint(Vec4 other) const;

            //Operators
            Vec4 operator+(const Vec4& other) const;
            Vec4 operator-(const Vec4& other) const;
            Vec4 operator*(const Vec4& other) const;
            Vec4 operator/(const Vec4& other) const;

            Vec4 operator+(const float& val) const;
            Vec4 operator-(const float& val) const;
            Vec4 operator*(const float& val) const;
            Vec4 operator/(const float& val) const;

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

            Vec4 operator-() const;

            Vec4& operator++();
            Vec4& operator--();

            bool operator<(const Vec4& other) const;
            bool operator>(const Vec4& other) const;
            bool operator<=(const Vec4& other) const;
            bool operator>=(const Vec4& other) const;
            bool operator==(const Vec4& other) const;
            bool operator!=(const Vec4& other) const;


        };

        class Color : public Vec4 {
        public:
            float& r = x;
            float& g = y;
            float& b = z;
            float& a = w;

            float& red   = x;
            float& green = y;
            float& blue  = z;
            float& alpha = w;

            Color(float r, float g, float b, float a=255);
            Color(float v = 255);
            Color(const hsv& hsv, float alpha = 255);

            hsv getHSV() const;
            void setHSV(const hsv& hcol);
        };


        //non-member operators
        std::ostream& operator<<(std::ostream& os, const Vec4& vec);

    }
}
