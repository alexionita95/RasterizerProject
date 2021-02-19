#pragma once
#include <vector>
#include "Vec3.h"

class Model {
private:
    std::vector<Vec3f> verts_;
    std::vector<std::vector<int> > faces_;
public:
    Model(const char *filename);
    ~Model();
    int vertexCount();
    int faceCount();
    Vec3f vertex(int i);
    std::vector<int> face(int idx);
};
