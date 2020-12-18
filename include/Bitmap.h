#pragma once
#include<stdint.h>

const int BYTES_PER_PIXEL = 3; /// red, green, & blue
const int FILE_HEADER_SIZE = 14;
const int INFO_HEADER_SIZE = 40;
struct BitmapColor {
    uint8_t r;
    uint8_t g;
    uint8_t b;

    BitmapColor()
        :r{ 0 }
        , g{ 0 }
        , b{ 0 }
    {

    }
    BitmapColor(uint8_t r_, uint8_t g_, uint8_t b_)
        :r{ r_ }
        , g{ g_ }
        , b{ b_ }{

    }
};
struct BitmapFileHeader {
    uint32_t fileSize = 0;
    uint32_t reserved = 0;
    uint32_t offset = 0;
};
struct BitmapInfoHeader {
    uint32_t size = 40;
    uint32_t widht = 0;
    uint32_t height = 0;
    uint16_t planes = 1;
    uint16_t bitCount = 24;
    uint32_t compression = 0;
    uint32_t imageSize = 0;
    uint32_t xPixelPerM = 0;
    uint32_t yPixelPerM = 0;
    uint32_t colorsUsed = 0;
    uint32_t colorsImportant = 0;
};
class Bitmap
{
public:
    Bitmap(uint32_t width_, uint32_t height_);
    Bitmap(uint32_t width_, uint32_t height_,uint8_t* buffer);
    ~Bitmap()
    {
        if (buffer)
        {
            delete[] buffer;
        }
    }
    void save(const char* filename);
    void setPixel(const uint32_t& x, const uint32_t& y, const BitmapColor& color);
    void setPixel(const uint32_t& x, const uint32_t& y, uint8_t r, uint8_t g, uint8_t b);

private:
    void createFileHeader();
    void createInfoHeader();
    void init();
    BitmapFileHeader fileHeader;
    BitmapInfoHeader infoHeader;
    uint32_t width;
    uint32_t widthInBytes;
    uint32_t height;
    uint8_t* buffer;
    uint32_t bufferSize;
    uint32_t paddingSize;
};