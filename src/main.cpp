#include<string>
#include<iostream>
#include <math.h>
#include <time.h>
#include "Bitmap.h"
#include "Renderer.h"
/*
const float PI = std::atan(1.0) * 4;
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
*/
int main()
{
    srand(time(NULL));
    char* fileName = "D:\\test.bmp";
    int screenWidth = 800;
    int screenHeight = 800;
    Renderer* renderer = new Renderer(screenWidth, screenHeight);
    Model* model = new Model("D:\\model.obj");
    renderer->renderModel(model);
    //renderer->triangle(Vec2i(10, 10), Vec2i(100, 70), Vec2i(150, 40), Color(255, 0, 0));
    //renderer->line(Vec2i(10, 10), Vec2i(100, 70), Color(255, 0, 0));
    Bitmap* bmp = new Bitmap(screenWidth,screenHeight,renderer->getBuffer());
    bmp->save(fileName);

    return 0;
}