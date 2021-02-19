#pragma once
#include <stdint.h>
#include "Vec3.h"
namespace Utils {
    static bool isInInterval(uint32_t value, uint32_t min, uint32_t max)
    {
        return min <= value && max > value;
    }
    template <typename T> 
    static Vec3<T> cross(Vec3<T>v1, Vec3<T> v2) 
    {
        return Vec3<T>(v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x);
    }

    static Vec3f world2screen(Vec3f v, const int& width, const int& height) {
        return Vec3f(int((v.x + 1.)*width / 2. + .5), int((v.y + 1.)*height / 2. + .5), v.z);
    }

    static Vec3f barycentric(Vec3f A, Vec3f B, Vec3f C, Vec3f P) {
        Vec3f s[3];
        s[2].x = C.z - A.z;
        s[2].y = B.z - A.z;
        s[2].z = A.z - P.z;

        s[1].x = C.y - A.y;
        s[1].y = B.y - A.y;
        s[1].z = A.y - P.y;

        s[0].x = C.x - A.x;
        s[0].y = B.x - A.x;
        s[0].z = A.x - P.x;
       
        Vec3f u = cross(s[0], s[1]);
        if (std::abs(u.z) > 1e-2) // dont forget that u[2] is integer. If it is zero then triangle ABC is degenerate
            return Vec3f(1.f - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z);
        return Vec3f(-1, 1, 1); // in this case generate negative coordinates, it will be thrown away by the rasterizator
    }
}