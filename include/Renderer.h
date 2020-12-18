#pragma once
#include<stdint.h>
#include "Vec2.h"
struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;

    Color()
        :r{ 0 }
        , g{ 0 }
        , b{ 0 }
    {

    }
    Color(uint8_t r_, uint8_t g_, uint8_t b_)
        :r{ r_ }
        , g{ g_ }
        , b{ b_ }{

    }
};
class Renderer
{
public:
    Renderer(uint32_t width_, uint32_t height_);
    ~Renderer()
    {
        if (buffer)
        {
            delete[] buffer;
        }
    }
    void setPixel(const uint32_t& x, const uint32_t& y, const Color& color);
    void setPixel(const uint32_t& x, const uint32_t& y, uint8_t r, uint8_t g, uint8_t b);
    uint8_t* getBuffer() {
        return buffer;
    }

    void line(const Vec2i& p0, const Vec2i& p1,const Color& c);

private:
    void init();
    uint32_t width;
    uint32_t widthInBytes;
    uint32_t height;
    uint8_t* buffer;
    uint32_t bufferSize;
};