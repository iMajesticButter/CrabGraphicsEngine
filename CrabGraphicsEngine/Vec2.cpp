#include "CrabVec2.h"
#include "CrabVec3.h"
#include "CrabVec4.h"

namespace CrabEngine {
    namespace Math {

        //constructors
        Vec2::Vec2(float x, float y) {

        }
        Vec2::Vec2(float v) {

        }
        Vec2::Vec2(const Vec2& other) {

        }
        Vec2::Vec2(const Vec3& other) {

        }
        Vec2::Vec2(const Vec4& other) {

        }

        //Public Funcs
        float Vec2::normalized() {

        }
        float Vec2::magnitude() {

        }
        float Vec2::magnitudeSquared() {

        }
        float Vec2::distance(Vec2 other) {

        }
        float Vec2::distanceSquared(Vec2 other) {

        }
        float Vec2::dot(Vec2 other) {

        }
        Vec3 Vec2::cross(Vec3 other) {

        }
        Vec2 Vec2::midpoint(Vec2 other) {

        }

        //Operators
        Vec2 Vec2::operator+(const Vec2& other) {

        }
        Vec2 Vec2::operator-(const Vec2& other) {

        }
        Vec2 Vec2::operator*(const Vec2& other) {

        }
        Vec2 Vec2::operator/(const Vec2& other) {

        }

        Vec2 Vec2::operator+(const float& val) {

        }
        Vec2 Vec2::operator-(const float& val) {

        }
        Vec2 Vec2::operator*(const float& val) {

        }
        Vec2 Vec2::operator/(const float& val) {

        }

        Vec2& Vec2::operator+=(const Vec2& other) {

        }
        Vec2& Vec2::operator-=(const Vec2& other) {

        }
        Vec2& Vec2::operator*=(const Vec2& other) {

        }
        Vec2& Vec2::operator/=(const Vec2& other) {

        }

        Vec2& Vec2::operator+=(const float& val) {

        }
        Vec2& Vec2::operator-=(const float& val) {

        }
        Vec2& Vec2::operator*=(const float& val) {

        }
        Vec2& Vec2::operator/=(const float& val) {

        }

        Vec2& Vec2::operator=(const Vec2& other) {

        }
        Vec2& Vec2::operator=(const float& val) {

        }

        Vec2 Vec2::operator-() {

        }

        Vec2& Vec2::operator++() {

        }
        Vec2& Vec2::operator--() {

        }

        bool Vec2::operator<(const Vec2& other) {

        }
        bool Vec2::operator>(const Vec2& other) {

        }
        bool Vec2::operator<=(const Vec2& other) {

        }
        bool Vec2::operator>=(const Vec2& other) {

        }
        bool Vec2::operator==(const Vec2& other) {

        }
        bool Vec2::operator!=(const Vec2& other) {

        }


        //non-member operators
        std::ostream& operator<<(std::ostream& os, const Vec2& vec) {
            return os << "(" << vec.x << ", " << vec.y << ")";
        }
    }
}
