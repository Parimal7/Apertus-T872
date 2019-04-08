#ifndef BMP_Headers_H
#define BMP_Headers_H

#include <cstdint>

#pragma pack(push, 1)

struct BMPFileHeader 
{
    uint16_t fileType =  0x4D42;
    uint32_t fileSize = 0;
    uint16_t reserved1 = 0;
    uint16_t reserved2 = 0;
    uint32_t offsetData = 0;
};

struct BMPInfoHeader
{
    uint32_t size = 0;
    uint32_t width = 0;
    uint32_t height = 0;
    uint16_t planes = 1;
    uint16_t bitCount = 0;
    uint32_t compression = 0;
    uint32_t sizeImage = 0;
    uint32_t xPixelsPerMeter = 0;
    uint32_t yPixelsPerMeter = 0;
    uint32_t colorsUsed = 0;
    uint32_t colorsImportant = 0;
};

struct BMPColorHeader 
{
    uint32_t redMask = 0x00ff0000;
    uint32_t greenMask = 0x0000ff00;
    uint32_t blueMask = 0x000000ff;
    uint32_t alphaMask = 0xff000000;
    uint32_t colorSpaceType = 0x73524742;
    uint32_t unused[16] = { 0 };
};

#pragma pack(pop)

#endif