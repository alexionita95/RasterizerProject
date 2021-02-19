#pragma once
#include <string>
template <typename T>
struct Vec3 {
    T x;
    T y;
    T z;
    Vec3() :x(0), y(0), z(0) {}
    Vec3(T x_, T y_, T z_) :x{ x_ }, y{ y_ }, z{ z_ } {}
    void translate(const Vec3<T>& value)
    {
        x = value.x;
        y = value.y;
        z = value.z;
    }
    inline Vec3<T> operator ^(const Vec3<T> &v) const { return Vec3<T>(y*v.z - z * v.y, z*v.x - x * v.z, x*v.y - y * v.x); }
    inline Vec3<T> operator +(const Vec3<T> &v) const { return Vec3<T>(x + v.x, y + v.y, z + v.z); }
    inline Vec3<T> operator -(const Vec3<T> &v) const { return Vec3<T>(x - v.x, y - v.y, z - v.z); }
    inline Vec3<T> operator *(float f)          const { return Vec3<T>(x*f, y*f, z*f); }
    inline T       operator *(const Vec3<T> &v) const { return x * v.x + y * v.y + z * v.z; }
    float norm() const { return std::sqrt(x*x + y * y + z * z); }
    Vec3<T> & normalize(T l = 1) { *this = (*this)*(l / norm()); return *this; }
    std::string toString()
    {
        return "(" + std::to_string(x) + "," + std::to_string(y) + +"," + std::to_string(z) ")";
    }
};
typedef Vec3<int32_t> Vec3i;
typedef Vec3<float> Vec3f;
