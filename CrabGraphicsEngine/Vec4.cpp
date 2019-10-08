#include "CrabVec2.h"
#include "CrabVec3.h"
#include "CrabVec4.h"

#include <math.h>
#include <algorithm>

namespace CrabEngine {
    namespace Math {

        //constructors
        Vec4::Vec4(float x, float y, float z, float w)
            : x(x), y(y), z(z), w(w) {

        }
        Vec4::Vec4(float v)
            : x(v), y(v), z(v), w(v) {

        }
        Vec4::Vec4(const Vec4& other)
            : x(other.x), y(other.y), z(other.z), w(other.w) {

        }
        Vec4::Vec4(const Vec3& v3, float v)
            : x(v3.x), y(v3.y), z(v3.z), w(v) {

        }
        Vec4::Vec4(float v, const Vec3& v3)
            : x(v), y(v3.x), z(v3.y), w(v3.z) {

        }
        Vec4::Vec4(const Vec2& v2, float z, float w)
            : x(v2.x), y(v2.y), z(z), w(w) {

        }
        Vec4::Vec4(float x, float y, const Vec2& v2)
            : x(x), y(y), z(v2.x), w(v2.y) {

        }
        Vec4::Vec4(float x, const Vec2& v2, float w)
            : x(x), y(v2.x), z(v2.y), w(w) {

        }
        Vec4::Vec4(const Vec2& vec2_1, const Vec2& vec2_2)
            : x(vec2_1.x), y(vec2_1.y), z(vec2_2.x), w(vec2_2.y) {

        }

        //Public Funcs
        Vec4 Vec4::normalized() const {
            return *this / magnitude();
        }
        float Vec4::magnitude() const {
            return sqrt(magnitudeSquared());
        }
        float Vec4::magnitudeSquared() const {
            return abs(x*x) +
                   abs(y*y) +
                   abs(z*z) +
                   abs(w*w);
        }
        float Vec4::distance(Vec4 other) const {
            return sqrt(distanceSquared(other));
        }
        float Vec4::distanceSquared(Vec4 other) const {
            return abs((x - other.x) * (x - other.x)) +
                   abs((y - other.y) * (y - other.y)) +
                   abs((z - other.z) * (z - other.z)) +
                   abs((w - other.w) * (w - other.w));
        }
        float Vec4::dot(Vec4 other) const {
            return x*other.x +
                   y*other.y +
                   z*other.z +
                   w*other.w;
        }
        Vec3 Vec4::cross(Vec3 other) const {
            return Vec3(y*other.z - z*other.y,
                        z*other.x - x*other.z,
                        x*other.y - y*other.x);
        }
        Vec4 Vec4::midpoint(Vec4 other) const {
            return Vec4(((x - other.x)/2)+other.x,
                        ((y - other.y)/2)+other.y,
                        ((z - other.z)/2)+other.z,
                        ((w - other.w)/2)+other.w);
        }

        //Operators
        Vec4 Vec4::operator+(const Vec4& other) const {
            return Vec4(x + other.x,
                        y + other.y,
                        z + other.z,
                        w + other.w);
        }
        Vec4 Vec4::operator-(const Vec4& other) const {
            return Vec4(x - other.x,
                        y - other.y,
                        z - other.z,
                        w - other.w);
        }
        Vec4 Vec4::operator*(const Vec4& other) const {
            return Vec4(x * other.x,
                        y * other.y,
                        z * other.z,
                        w * other.w);
        }
        Vec4 Vec4::operator/(const Vec4& other) const {
            return Vec4(x / other.x,
                        y / other.y,
                        z / other.z,
                        w / other.w);
        }

        Vec4 Vec4::operator+(const float& val) const {
            return Vec4(x + val,
                        y + val,
                        z + val,
                        w + val);
        }
        Vec4 Vec4::operator-(const float& val) const {
            return Vec4(x - val,
                        y - val,
                        z - val,
                        w - val);
        }
        Vec4 Vec4::operator*(const float& val) const {
            return Vec4(x * val,
                        y * val,
                        z * val,
                        w * val);
        }
        Vec4 Vec4::operator/(const float& val) const {
            return Vec4(x / val,
                        y / val,
                        z / val,
                        w / val);
        }

        Vec4& Vec4::operator+=(const Vec4& other) {
            x += other.x;
            y += other.y;
            z += other.z;
            w += other.w;
            return *this;
        }
        Vec4& Vec4::operator-=(const Vec4& other) {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            w -= other.w;
            return *this;
        }
        Vec4& Vec4::operator*=(const Vec4& other) {
            x *= other.x;
            y *= other.y;
            z *= other.z;
            w *= other.w;
            return *this;
        }
        Vec4& Vec4::operator/=(const Vec4& other) {
            x /= other.x;
            y /= other.y;
            z /= other.z;
            w /= other.w;
            return *this;
        }

        Vec4& Vec4::operator+=(const float& val) {
            x += val;
            y += val;
            z += val;
            w += val;
            return *this;
        }
        Vec4& Vec4::operator-=(const float& val) {
            x -= val;
            y -= val;
            z -= val;
            w -= val;
            return *this;
        }
        Vec4& Vec4::operator*=(const float& val) {
            x *= val;
            y *= val;
            z *= val;
            w *= val;
            return *this;
        }
        Vec4& Vec4::operator/=(const float& val) {
            x /= val;
            y /= val;
            z /= val;
            w /= val;
            return *this;
        }

        Vec4& Vec4::operator=(const Vec4& other) {
            x = other.x;
            y = other.y;
            z = other.z;
            w = other.w;
            return *this;
        }
        Vec4& Vec4::operator=(const float& val) {
            x = val;
            y = val;
            z = val;
            w = val;
            return *this;
        }

        Vec4 Vec4::operator-() const {
            return Vec4(-x,-y,-z,-w);
        }

        Vec4& Vec4::operator++() {
            ++x;
            ++y;
            ++z;
            ++w;
            return *this;
        }
        Vec4& Vec4::operator--() {
            --x;
            --y;
            --z;
            --w;
            return *this;
        }

        bool Vec4::operator<(const Vec4& other) const {
            return magnitude() < other.magnitude();
        }
        bool Vec4::operator>(const Vec4& other) const {
            return magnitude() > other.magnitude();
        }
        bool Vec4::operator<=(const Vec4& other) const {
            return magnitude() <= other.magnitude();
        }
        bool Vec4::operator>=(const Vec4& other) const {
            return magnitude() >= other.magnitude();
        }
        bool Vec4::operator==(const Vec4& other) const {
            return x == other.x &&
                   y == other.y &&
                   z == other.z &&
                   w == other.w;
        }
        bool Vec4::operator!=(const Vec4& other) const {
            return x != other.x ||
                   y != other.y ||
                   z != other.z ||
                   w != other.w;
        }


        //non-member operators
        std::ostream& operator<<(std::ostream& os, const Vec4& vec) {
            return os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
        }

        //Color

        Color::Color(float r, float g, float b, float a) : Vec4(r, g, b, a) {
        }
        Color::Color(float v) : Vec4(v) {
        }
        Color::Color(const hsv& hsv, float alpha) : Vec4(alpha) {
            setHSV(hsv);
        }

        hsv Color::getHSV() const {
            hsv hcol;

            float r = this->r/255;
            float g = this->g/255;
            float b = this->b/255;

            float cmax = std::max(r,std::max(g,b));
            float cmin = std::min(r,std::min(g,b));

            if(cmax == cmin) {
                hcol.h = 0;
                hcol.s = 0;
                hcol.v = cmin;
                return hcol;
            }

            float d = (r==cmin) ? g-b : ((b==cmin) ? r-g : b-r);
            float h = (r==cmin) ? 3 : ((b == cmin) ? 1 : 5);

            hcol.h = 60*(h-d/(cmax-cmin));
            hcol.s = (cmax - cmin)/cmax;
            hcol.v = cmax;

            return hcol;
        }
        void Color::setHSV(const hsv& hcol) {

            float c = hcol.s*hcol.v;
            float x = c*(1-abs(fmod(hcol.h/60.0f, 2)-1));
            float m = hcol.v = c;
            float rs, gs, bs;

            if(hcol.h >= 0 && hcol.h < 60) {
                rs = c;
                gs = x;
                bs = 0;
            } else if(hcol.h >= 60 && hcol.h < 120) {
                rs = x;
                gs = c;
                bs = 0;
            } else if(hcol.h >= 120 && hcol.h < 180) {
                rs = 0;
                gs = c;
                bs = x;
            } else if(hcol.h >= 240 && hcol.h < 300) {
                rs = x;
                gs = 0;
                bs = c;
            } else {
                rs = c;
                gs = 0;
                bs = x;
            }

            r = (rs+m)*255;
            g = (gs+m)*255;
            b = (bs+m)*255;
        }
    }
}
