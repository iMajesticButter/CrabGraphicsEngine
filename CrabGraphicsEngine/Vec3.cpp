#include "CrabVec2.h"
#include "CrabVec3.h"
#include "CrabVec4.h"

namespace CrabEngine {
    namespace Math {

        //constructors
        Vec3::Vec3(float x, float y, float z) {

        }
        Vec3::Vec3(float v) {

        }
        Vec3::Vec3(const Vec3& other) {

        }
        Vec3::Vec3(const Vec2& v2, float v) {

        }
        Vec3::Vec3(float v, const Vec2& v2) {

        }
        Vec3::Vec3(const Vec4& other) {

        }

        //Public Funcs
        float Vec3::normalized() {

        }
        float Vec3::magnitude() {

        }
        float Vec3::magnitudeSquared() {

        }
        float Vec3::distance(Vec3 other) {

        }
        float Vec3::distanceSquared(Vec3 other) {

        }
        float Vec3::dot(Vec3 other) {

        }
        Vec3 Vec3::cross(Vec3 other) {

        }
        Vec3 Vec3::midpoint(Vec3 other) {

        }
        Vec3 Vec3::getHSV() {

        }
        void Vec3::setHSV(Vec3 hsv) {

        }
        Vec4 Vec3::getColor() {

        }

        //Operators
        Vec3 Vec3::operator+(const Vec3& other) {

        }
        Vec3 Vec3::operator-(const Vec3& other) {

        }
        Vec3 Vec3::operator*(const Vec3& other) {

        }
        Vec3 Vec3::operator/(const Vec3& other) {

        }

        Vec3 Vec3::operator+(const float& val) {

        }
        Vec3 Vec3::operator-(const float& val) {

        }
        Vec3 Vec3::operator*(const float& val) {

        }
        Vec3 Vec3::operator/(const float& val) {

        }

        Vec3& Vec3::operator+=(const Vec3& other) {

        }
        Vec3& Vec3::operator-=(const Vec3& other) {

        }
        Vec3& Vec3::operator*=(const Vec3& other) {

        }
        Vec3& Vec3::operator/=(const Vec3& other) {

        }

        Vec3& Vec3::operator+=(const float& val) {

        }
        Vec3& Vec3::operator-=(const float& val) {

        }
        Vec3& Vec3::operator*=(const float& val) {

        }
        Vec3& Vec3::operator/=(const float& val) {

        }

        Vec3& Vec3::operator=(const Vec3& other) {

        }
        Vec3& Vec3::operator=(const float& val) {

        }

        Vec3 Vec3::operator-() {

        }

        Vec3& Vec3::operator++() {

        }
        Vec3& Vec3::operator--() {

        }

        bool Vec3::operator<(const Vec3& other) {

        }
        bool Vec3::operator>(const Vec3& other) {

        }
        bool Vec3::operator<=(const Vec3& other) {

        }
        bool Vec3::operator>=(const Vec3& other) {

        }
        bool Vec3::operator==(const Vec3& other) {

        }
        bool Vec3::operator!=(const Vec3& other) {

        }


        //non-member operators
        std::ostream& operator<<(std::ostream& os, const Vec3& vec) {
            return os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
        }
    }
}
