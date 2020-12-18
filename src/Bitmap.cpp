#include "Bitmap.h"
#include <memory>
#include "Utils.h"
#include <fstream>

Bitmap::Bitmap(uint32_t width_, uint32_t height_)
    :width{width_}
    ,height{height_}
{
    init();

}

Bitmap::Bitmap(uint32_t width_, uint32_t height_, uint8_t * buffer_)
    :width{ width_ }
    , height{ height_ }
{
    init();
    memcpy(buffer, buffer_, bufferSize);
}

void Bitmap::save(const char * filename)
{

    uint8_t padding[3] = { 0, 0, 0 };
    
    std::ofstream file(filename, std::ofstream::binary);
    char signature[2] = { 'B','M' };
    file.write(signature, 2);
    file.write((char*)&fileHeader , FILE_HEADER_SIZE-2);
    file.write((char*)&infoHeader , INFO_HEADER_SIZE);
    for (int i = 0; i < height; i++) {
        file.write((char*)(buffer + widthInBytes * i), widthInBytes);
        if (paddingSize != 0)
        {
            file.write((char*)padding, paddingSize);
        }
    }
    file.flush();
    file.close();

}

void Bitmap::setPixel(const uint32_t & x, const uint32_t & y, const BitmapColor & color)
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

void Bitmap::setPixel(const uint32_t & x, const uint32_t & y, uint8_t r, uint8_t g, uint8_t b)
{
    BitmapColor color(r, g, b);
    setPixel(x, y, color);
}

void Bitmap::createFileHeader()
{

    fileHeader.fileSize = (widthInBytes + paddingSize)*height + FILE_HEADER_SIZE + INFO_HEADER_SIZE;
    fileHeader.offset = FILE_HEADER_SIZE + INFO_HEADER_SIZE;
}

void Bitmap::createInfoHeader()
{
    infoHeader.size = INFO_HEADER_SIZE;
    infoHeader.widht = width;
    infoHeader.height = height;
}

void Bitmap::init()
{
    bufferSize = width * height * BYTES_PER_PIXEL;
    buffer = new uint8_t[bufferSize];
    memset(buffer, 0, bufferSize);
    widthInBytes = width * BYTES_PER_PIXEL;
    paddingSize = (4 - (widthInBytes) % 4) % 4;
    createFileHeader();
    createInfoHeader();
}
