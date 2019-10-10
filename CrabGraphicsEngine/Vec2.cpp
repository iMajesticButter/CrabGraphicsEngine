#include "CrabVec2.h"
#include "CrabVec3.h"
#include "CrabVec4.h"

#include <math.h>

namespace CrabEngine {
    namespace Math {

        //constructors
        Vec2::Vec2(float x, float y) : x(x), y(y) {

        }
        Vec2::Vec2(float v) : x(v), y(v) {

        }
        Vec2::Vec2(const Vec2& other) : x(other.x), y(other.y) {

        }
        Vec2::Vec2(const Vec3& other) : x(other.x), y(other.y) {

        }
        Vec2::Vec2(const Vec4& other) : x(other.x), y(other.y) {

        }

        //Public Funcs
        Vec2 Vec2::normalized() const {
            return *this / magnitude();
        }
        float Vec2::magnitude() const {
            return sqrt(magnitudeSquared());
        }
        float Vec2::magnitudeSquared() const {
            return abs(x*x) + abs(y*y);
        }
        float Vec2::distance(Vec2 other) const {
            return sqrt(distanceSquared(other));
        }
        float Vec2::distanceSquared(Vec2 other) const {
            return abs((x-other.x)*(x-other.x)) + abs((y-other.y)*(y-other.y));
        }
        float Vec2::dot(Vec2 other) const {
            return x*other.x + y*other.y;
        }
        Vec3 Vec2::cross(Vec3 other) const {
            return Vec3(y*other.z - 0*other.y,
                        0*other.x - x*other.z,
                        x*other.y - y*other.x);
        }
        Vec2 Vec2::midpoint(Vec2 other) const {
            return Vec2(((x - other.x)/2)+other.x, ((y - other.y)/2)+other.y);
        }

        //Operators
        Vec2 Vec2::operator+(const Vec2& other) const {
            return Vec2(x + other.x,
                        y + other.y);
        }
        Vec2 Vec2::operator-(const Vec2& other) const {
            return Vec2(x - other.x,
                        y - other.y);
        }
        Vec2 Vec2::operator*(const Vec2& other) const {
            return Vec2(x * other.x,
                        y * other.y);
        }
        Vec2 Vec2::operator/(const Vec2& other) const {
            return Vec2(x / other.x,
                        y / other.y);
        }

        Vec2 Vec2::operator+(const float& val) const {
            return Vec2(x + val,
                        y + val);
        }
        Vec2 Vec2::operator-(const float& val) const {
            return Vec2(x - val,
                        y - val);
        }
        Vec2 Vec2::operator*(const float& val) const {
            return Vec2(x * val,
                        y * val);
        }
        Vec2 Vec2::operator/(const float& val) const {
            return Vec2(x / val,
                        y / val);
        }

        Vec2& Vec2::operator+=(const Vec2& other) {
            x += other.x;
            y += other.y;
            return *this;
        }
        Vec2& Vec2::operator-=(const Vec2& other) {
            x -= other.x;
            y -= other.y;
            return *this;
        }
        Vec2& Vec2::operator*=(const Vec2& other) {
            x *= other.x;
            y *= other.y;
            return *this;
        }
        Vec2& Vec2::operator/=(const Vec2& other) {
            x /= other.x;
            y /= other.y;
            return *this;
        }

        Vec2& Vec2::operator+=(const float& val) {
            x += val;
            y += val;
            return *this;
        }
        Vec2& Vec2::operator-=(const float& val) {
            x -= val;
            y -= val;
            return *this;
        }
        Vec2& Vec2::operator*=(const float& val) {
            x *= val;
            y *= val;
            return *this;
        }
        Vec2& Vec2::operator/=(const float& val) {
            x /= val;
            y /= val;
            return *this;
        }

        Vec2& Vec2::operator=(const Vec2& other) {
            x = other.x;
            y = other.y;
            return *this;
        }
        Vec2& Vec2::operator=(const float& val) {
            x = val;
            y = val;
            return *this;
        }

        Vec2 Vec2::operator-() const {
            return Vec2(-x, -y);
        }

        Vec2& Vec2::operator++() {
            ++x;
            ++y;
            return *this;
        }
        Vec2& Vec2::operator--() {
            --x;
            --y;
            return *this;
        }

        bool Vec2::operator<(const Vec2& other) const {
            return magnitude() < other.magnitude();
        }
        bool Vec2::operator>(const Vec2& other) const {
            return magnitude() > other.magnitude();
        }
        bool Vec2::operator<=(const Vec2& other) const {
            return magnitude() <= other.magnitude();
        }
        bool Vec2::operator>=(const Vec2& other) const {
            return magnitude() >= other.magnitude();
        }
        bool Vec2::operator==(const Vec2& other) const {
            return x == other.x &&
                   y == other.y;
        }
        bool Vec2::operator!=(const Vec2& other) const {
            return x != other.x ||
                   y != other.y;
        }


        //non-member operators
        std::ostream& operator<<(std::ostream& os, const Vec2& vec) {
            return os << "(" << vec.x << ", " << vec.y << ")";
        }
        Vec2 operator*(float val, const Vec2& vec) {
            return vec * val;
        }
    }
}
