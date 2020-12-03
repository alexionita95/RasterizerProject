#include<string>
#include<iostream>
#include <math.h>
const float PI = std::atan(1.0) * 4;
struct Vec3 {
    float x;
    float y;
    float z;
    Vec3() :x(0), y(0), z(0) {}
    Vec3(float x_, float y_, float z_) :x(x_), y(y_), z(z_) {}
    Vec3 operator +(const Vec3& other)
    {
        return Vec3(x + other.x, y + other.y, z + other.z);
    }
    Vec3 operator -(const Vec3& other)
    {
        return Vec3(x - other.x, y - other.y, z - other.z);
    }
    Vec3 operator *(const Vec3& other)
    {
        return Vec3(y*other.z - z * other.y, z*other.x - x * other.z, x*other.y - y * other.x);
    }

    void rotateXY(float degrees)
    {
        Mat3 rotation = Mat3::XYRotation(degrees);
        *this = rotation.multiply(*this);
    }
    void rotateXZ(float degrees)
    {
        Mat3 rotation = Mat3::XZRotation(degrees);
        *this = rotation.multiply(*this);
    }
    void rotateYZ(float degrees)
    {
        Mat3 rotation = Mat3::YZRotation(degrees);
        *this = rotation.multiply(*this);
    }
    void scale(const Vec3& scale)
    {
        Mat3 scaleMatrix = Mat3::scale(scale);
        *this = scaleMatrix.multiply(*this);
    }
    void translate(const Vec3& value)
    {
        x = value.x;
        y = value.y;
        z = value.z;
    }

    std::string toString()
    {
        return "(" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + ")";
    }
};

struct Mat3 {
    static const int size = 3;
    float arr[size][size];
    Mat3()
    {
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                arr[i][j] = 0;
            }
        }
    }
    std::string toString()
    {
        std::string result;
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                if (j != size - 1) {
                    result += std::to_string(arr[i][j]) + ", ";
                }
                else
                {
                    result += std::to_string(arr[i][j]) + "\n";
                }
            }
        }
        return result;
    }
    static Mat3 identity()
    {
        Mat3 result;
        for (int i = 0; i < size; ++i)
        {
            result.arr[i][i] = 1;
        }
        return result;
    }
    static Mat3 XYRotation(float degree)
    {
        Mat3 result = identity();
        float theta = degree * PI / 180.0f;
        float sin = std::sin(theta);
        float cos = std::cos(theta);
        result.arr[0][0] = cos;
        result.arr[0][1] = -sin;
        result.arr[1][0] = sin;
        result.arr[1][1] = cos;

    }
    static Mat3 XZRotation(float degree)
    {
        Mat3 result = identity();
        float theta = degree * PI / 180.0f;
        float sin = std::sin(theta);
        float cos = std::cos(theta);
        result.arr[0][0] = cos;
        result.arr[0][2] = sin;
        result.arr[2][0] = -sin;
        result.arr[2][2] = cos;

    }
    static Mat3 YZRotation(float degree)
    {
        Mat3 result = identity();
        float theta = degree * PI / 180.0f;
        float sin = std::sin(theta);
        float cos = std::cos(theta);
        result.arr[1][1] = cos;
        result.arr[1][2] = -sin;
        result.arr[2][1] = sin;
        result.arr[2][2] = cos;

    }
    static Mat3 scale(const Vec3& scale)
    {
        Mat3 result;
        result.arr[0][0] = scale.x;
        result.arr[1][1] = scale.y;
        result.arr[2][2] = scale.z;
        return result;
    }
    Vec3 multiply(const Vec3& vec)
    {
        return Vec3(arr[0][0] * vec.x + arr[0][1] * vec.y + arr[0][2] * vec.z, arr[1][0] * vec.x + arr[1][1] * vec.y + arr[1][2] * vec.z, arr[2][0] * vec.x + arr[2][1] * vec.y + arr[2][2] * vec.z);
    }

};

int main()
{

    Mat3 m = Mat3::identity();
    std::cout << m.toString() << std::endl;
    return 0;
}