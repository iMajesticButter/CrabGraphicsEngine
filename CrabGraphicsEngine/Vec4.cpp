#include "CrabVec2.h"
#include "CrabVec3.h"
#include "CrabVec4.h"

namespace CrabEngine {
    namespace Math {

        //constructors
        Vec4::Vec4(float x, float y, float z, float w) {

        }
        Vec4::Vec4(float v) {

        }
        Vec4::Vec4(const Vec4& other) {

        }
        Vec4::Vec4(const Vec3& v3, float v) {

        }
        Vec4::Vec4(float v, const Vec3& v3) {

        }
        Vec4::Vec4(const Vec2& v2, float z, float w) {

        }
        Vec4::Vec4(float x, float y, const Vec2& v2) {

        }
        Vec4::Vec4(float x, const Vec2& v2, float w) {

        }
        Vec4::Vec4(const Vec2& vec2_1, const Vec2& vec2_2) {

        }

        //Public Funcs
        float Vec4::normalized() {

        }
        float Vec4::magnitude() {

        }
        float Vec4::magnitudeSquared() {

        }
        float Vec4::distance(Vec4 other) {

        }
        float Vec4::distanceSquared(Vec4 other) {

        }
        float Vec4::dot(Vec4 other) {

        }
        Vec3 Vec4::cross(Vec3 other) {

        }
        Vec4 Vec4::midpoint(Vec2 other) {

        }
        Vec3 Vec4::getHSV() {

        }
        void Vec4::setHSV(Vec3 hsv) {

        }

        //Operators
        Vec4 Vec4::operator+(const Vec4& other) {

        }
        Vec4 Vec4::operator-(const Vec4& other) {

        }
        Vec4 Vec4::operator*(const Vec4& other) {

        }
        Vec4 Vec4::operator/(const Vec4& other) {

        }

        Vec4 Vec4::operator+(const float& val) {

        }
        Vec4 Vec4::operator-(const float& val) {

        }
        Vec4 Vec4::operator*(const float& val) {

        }
        Vec4 Vec4::operator/(const float& val) {

        }

        Vec4& Vec4::operator+=(const Vec4& other) {

        }
        Vec4& Vec4::operator-=(const Vec4& other) {

        }
        Vec4& Vec4::operator*=(const Vec4& other) {

        }
        Vec4& Vec4::operator/=(const Vec4& other) {

        }

        Vec4& Vec4::operator+=(const float& val) {

        }
        Vec4& Vec4::operator-=(const float& val) {

        }
        Vec4& Vec4::operator*=(const float& val) {

        }
        Vec4& Vec4::operator/=(const float& val) {

        }

        Vec4& Vec4::operator=(const Vec4& other) {

        }
        Vec4& Vec4::operator=(const float& val) {

        }

        Vec4 Vec4::operator-() {

        }

        Vec4& Vec4::operator++() {

        }
        Vec4& Vec4::operator--() {

        }

        bool Vec4::operator<(const Vec4& other) {

        }
        bool Vec4::operator>(const Vec4& other) {

        }
        bool Vec4::operator<=(const Vec4& other) {

        }
        bool Vec4::operator>=(const Vec4& other) {

        }
        bool Vec4::operator==(const Vec4& other) {

        }
        bool Vec4::operator!=(const Vec4& other) {

        }


        //non-member operators
        std::ostream& operator<<(std::ostream& os, const Vec4& vec) {
            return os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
        }

    }
}
