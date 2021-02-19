#include "Renderer.h"
#include <memory>
#include "Utils.h"
#include <fstream>
#include <cmath>
#include <algorithm>


Renderer::Renderer(uint32_t width_, uint32_t height_)
    :width{ width_ }
    , height{ height_ }
{
    init();

}



void Renderer::setPixel(const uint32_t & x, const uint32_t & y, const Color & color)
{
    if (!buffer)
    {
        printf("No buffer\n");
        return;
    }
    if (!Utils::isInInterval(x, 0, width) || !Utils::isInInterval(y, 0, height))
    {
        printf("Not in range! %i, %i\n", x, y);
        return;

    }
    buffer[widthInBytes*y + x * 3] = color.b;
    buffer[widthInBytes*y + x * 3 + 1] = color.g;
    buffer[widthInBytes*y + x * 3 + 2] = color.r;
}

void Renderer::setPixel(const uint32_t & x, const uint32_t & y, uint8_t r, uint8_t g, uint8_t b)
{
    Color color(r, g, b);
    setPixel(x, y, color);
}


void Renderer::line(const Vec2i& p0, const Vec2i& p1, const Color& c)
{

    int x0 = p0.x;
    int x1 = p1.x;
    int y0 = p0.y;
    int y1 = p1.y;

    bool steep = false;
    if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    for (int x = x0; x <= x1; x++) {
        float t = (x - x0) / (float)(x1 - x0);
        int y = y0 * (1. - t) + y1 * t;
        if (steep) {
            setPixel(y, x, c);
        }
        else {
            setPixel(x, y, c);

        }
    }
}

void Renderer::triangle(const Vec2i & p0, const Vec2i & p1, const Vec2i & p2, const Color & c)
{
    Vec2i t0 = p0;
    Vec2i t1 = p1;
    Vec2i t2 = p2;

    if (t0.y == t1.y && t0.y == t2.y) return; // i dont care about degenerate triangles
    if (t0.y > t1.y) std::swap(t0, t1);
    if (t0.y > t2.y) std::swap(t0, t2);
    if (t1.y > t2.y) std::swap(t1, t2);
    int total_height = t2.y - t0.y;
    for (int i = 0; i < total_height; i++) {
        bool second_half = i > t1.y - t0.y || t1.y == t0.y;
        int segment_height = second_half ? t2.y - t1.y : t1.y - t0.y;
        float alpha = (float)i / total_height;
        float beta = (float)(i - (second_half ? t1.y - t0.y : 0)) / segment_height; // be careful: with above conditions no division by zero here
        Vec2i A = t0 + (t2 - t0)*alpha;
        Vec2i B = second_half ? t1 + (t2 - t1)*beta : t0 + (t1 - t0)*beta;
        if (A.x > B.x) std::swap(A, B);
        for (int j = A.x; j <= B.x; j++) {
            setPixel(j, t0.y + i, c); // attention, due to int casts t0.y+i != A.y
        }
    }
}

void Renderer::triangle(Vec3f *pts, const Color& c) {
    Vec2f bboxmin(std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
    Vec2f bboxmax(-std::numeric_limits<float>::max(), -std::numeric_limits<float>::max());
    Vec2f clamp(width- 1, height - 1);
    for (int i = 0; i < 3; i++) {

        bboxmin.x = std::max(0.f, std::min(bboxmin.x, pts[i].x));
        bboxmin.y = std::max(0.f, std::min(bboxmin.y, pts[i].y));

        bboxmax.x = std::min(clamp.x, std::max(bboxmax.x, pts[i].x));
        bboxmax.y = std::min(clamp.y, std::max(bboxmax.y, pts[i].y));
    }
    Vec3f P;
    for (P.x = bboxmin.x; P.x <= bboxmax.x; P.x++) {
        for (P.y = bboxmin.y; P.y <= bboxmax.y; P.y++) {
            Vec3f bc_screen = Utils::barycentric(pts[0], pts[1], pts[2], P);
            if (bc_screen.x < 0 || bc_screen.y < 0 || bc_screen.z < 0) continue;
            P.z = 0;

            P.z += pts[0].z*bc_screen.x;
            P.z += pts[1].z*bc_screen.y;
            P.z += pts[2].z*bc_screen.z;
            if (zbuffer[int(P.x + P.y*width)] < P.z) {
                zbuffer[int(P.x + P.y*width)] = P.z;
                setPixel(P.x, P.y, c);
            }
        }
    }
}

void Renderer::renderModel(Model * model)
{
    for (int i = 0; i < model->faceCount(); i++) {
        std::vector<int> face = model->face(i);
        Vec3f pts[3];
        for (int i = 0; i < 3; i++) pts[i] = Utils::world2screen(model->vertex(face[i]),width,height);
        triangle(pts, Color(255,255,255, 255));
    }

}

void Renderer::init()
{
    const int BYTES_PER_PIXEL = 3; /// red, green, & blue
    widthInBytes = width * BYTES_PER_PIXEL;
    bufferSize = widthInBytes * height;
    buffer = new uint8_t[bufferSize];
    zbuffer = new int[width*height];
    memset(buffer, 0, bufferSize);
    for (int i = width * height; i--; zbuffer[i] = -std::numeric_limits<float>::max());

}
