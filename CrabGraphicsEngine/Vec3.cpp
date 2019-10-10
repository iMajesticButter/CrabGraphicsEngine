#include "CrabVec2.h"
#include "CrabVec3.h"
#include "CrabVec4.h"

#include <math.h>

namespace CrabEngine {
    namespace Math {

        //constructors
        Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {

        }
        Vec3::Vec3(float v) : x(v), y(v), z(v) {

        }
        Vec3::Vec3(const Vec3& other) : x(other.x), y(other.y), z(other.z) {

        }
        Vec3::Vec3(const Vec2& v2, float v) : x(v2.x), y(v2.y), z(v) {

        }
        Vec3::Vec3(float v, const Vec2& v2) : x(v), y(v2.x), z(v2.y) {

        }
        Vec3::Vec3(const Vec4& other) : x(other.x), y(other.y), z(other.z) {

        }

        //Public Funcs
        Vec3 Vec3::normalized() const {
            return *this / magnitude();
        }
        float Vec3::magnitude() const {
            return sqrt(magnitudeSquared());
        }
        float Vec3::magnitudeSquared() const {
            return abs(x*x) +
                   abs(y*y) +
                   abs(z*z);
        }
        float Vec3::distance(Vec3 other) const {
            return sqrt(distanceSquared(other));
        }
        float Vec3::distanceSquared(Vec3 other) const {
            return abs((x - other.x)*(x - other.x)) +
                   abs((y - other.y)*(y - other.y)) +
                   abs((z - other.z)*(z - other.z));
        }
        float Vec3::dot(Vec3 other) const {
            return x*other.x +
                   y*other.y +
                   z*other.z;
        }
        Vec3 Vec3::cross(Vec3 other) const {
            return Vec3(y*other.z - z*other.y,
                        z*other.x - x*other.z,
                        x*other.y - y*other.x);
        }
        Vec3 Vec3::midpoint(Vec3 other) const {
            return Vec3(((x - other.x)/2)+other.x,
                        ((y - other.y)/2)+other.y,
                        ((z - other.z)/2)+other.z);
        }

        //Operators
        Vec3 Vec3::operator+(const Vec3& other) const {
            return Vec3(x + other.x,
                        y + other.y,
                        z + other.z);
        }
        Vec3 Vec3::operator-(const Vec3& other) const {
            return Vec3(x - other.x,
                        y - other.y,
                        z - other.z);
        }
        Vec3 Vec3::operator*(const Vec3& other) const {
            return Vec3(x * other.x,
                        y * other.y,
                        z * other.z);
        }
        Vec3 Vec3::operator/(const Vec3& other) const {
            return Vec3(x / other.x,
                        y / other.y,
                        z / other.z);
        }

        Vec3 Vec3::operator+(const float& val) const {
            return Vec3(x + val,
                        y + val,
                        z + val);
        }
        Vec3 Vec3::operator-(const float& val) const {
            return Vec3(x - val,
                        y - val,
                        z - val);
        }
        Vec3 Vec3::operator*(const float& val) const {
            return Vec3(x * val,
                        y * val,
                        z * val);
        }
        Vec3 Vec3::operator/(const float& val) const {
            return Vec3(x / val,
                        y / val,
                        z / val);
        }

        Vec3& Vec3::operator+=(const Vec3& other) {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }
        Vec3& Vec3::operator-=(const Vec3& other) {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            return *this;
        }
        Vec3& Vec3::operator*=(const Vec3& other) {
            x *= other.x;
            y *= other.y;
            z *= other.z;
            return *this;
        }
        Vec3& Vec3::operator/=(const Vec3& other) {
            x /= other.x;
            y /= other.y;
            z /= other.z;
            return *this;
        }

        Vec3& Vec3::operator+=(const float& val) {
            x += val;
            y += val;
            z += val;
            return *this;
        }
        Vec3& Vec3::operator-=(const float& val) {
            x -= val;
            y -= val;
            z -= val;
            return *this;
        }
        Vec3& Vec3::operator*=(const float& val) {
            x *= val;
            y *= val;
            z *= val;
            return *this;
        }
        Vec3& Vec3::operator/=(const float& val) {
            x /= val;
            y /= val;
            z /= val;
            return *this;
        }

        Vec3& Vec3::operator=(const Vec3& other) {
            x = other.x;
            y = other.y;
            z = other.z;
            return *this;
        }
        Vec3& Vec3::operator=(const float& val) {
            x = val;
            y = val;
            z = val;
            return *this;
        }

        Vec3 Vec3::operator-() const {
            return Vec3(-x,-y,-z);
        }

        Vec3& Vec3::operator++() {
            ++x;
            ++y;
            ++z;
            return  *this;
        }
        Vec3& Vec3::operator--() {
            --x;
            --y;
            --z;
            return  *this;
        }

        bool Vec3::operator<(const Vec3& other) const {
            return magnitude() < other.magnitude();
        }
        bool Vec3::operator>(const Vec3& other) const {
            return magnitude() > other.magnitude();
        }
        bool Vec3::operator<=(const Vec3& other) const {
            return magnitude() <= other.magnitude();
        }
        bool Vec3::operator>=(const Vec3& other) const {
            return magnitude() >= other.magnitude();
        }
        bool Vec3::operator==(const Vec3& other) const {
            return x == other.x &&
                   y == other.y &&
                   z == other.z;
        }
        bool Vec3::operator!=(const Vec3& other) const {
            return x != other.x ||
                   y != other.y ||
                   z != other.z;
        }


        //non-member operators
        std::ostream& operator<<(std::ostream& os, const Vec3& vec) {
            return os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
        }
        Vec2 operator*(float val, const Vec3& vec) {
            return vec * val;
        }
    }
}
