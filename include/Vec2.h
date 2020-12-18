#pragma once
#include <string>
template <typename T>
struct Vec2 {
    T x;
    T y;
    Vec2() :x(0), y(0), z(0) {}
    Vec2(T x_, T y_) :x{ x_ }, y{ y_ } {}
    Vec2<T> operator +(const Vec2<T>& other)
    {
        return Vec2<T>(x + other.x, y + other.y);
    }
    Vec2<T> operator -(const Vec2<T>& other)
    {
        return Vec2<T>(x - other.x, y - other.y, z - other.z);
    }

    void translate(const Vec2<T>& value)
    {
        x = value.x;
        y = value.y;
    }

    std::string toString()
    {
        return "(" + std::to_string(x) + "," + std::to_string(y) + ")";
    }
};
typedef Vec2<int32_t> Vec2i;
typedef Vec2<float> Vec2f;
