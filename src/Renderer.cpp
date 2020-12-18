#include "Renderer.h"
#include <memory>
#include "Utils.h"
#include <fstream>

Renderer::Renderer(uint32_t width_, uint32_t height_)
    :width{width_}
    ,height{height_}
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
        printf("Not in range!\n");
        return;
       
    }
    buffer[widthInBytes*y + x*3] = color.b;
    buffer[widthInBytes*y + x*3 + 1] = color.g;
    buffer[widthInBytes*y + x*3 + 2] = color.r;
}

void Renderer::setPixel(const uint32_t & x, const uint32_t & y, uint8_t r, uint8_t g, uint8_t b)
{
    Color color(r, g, b);
    setPixel(x, y, color);
}


void Renderer::line(const Vec2i& p0, const Vec2i& p1, const Color& c)
{
    for (float t = 0.; t < 1.; t += .01) {
        int x = p0.x + (p1.x - p0.x)*t;
        int y = p0.y + (p1.y - p0.y)*t;
        setPixel(x, y, c);
    }
}

void Renderer::init()
{
    const int BYTES_PER_PIXEL = 3; /// red, green, & blue
    bufferSize = width * height * 3;
    buffer = new uint8_t[bufferSize];
    memset(buffer, 0, bufferSize);
    widthInBytes = width * BYTES_PER_PIXEL;
}
