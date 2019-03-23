#include <fstream>
#include <vector>
#include "BMP.hpp"

BMP::BMP(int32_t width, int32_t height) 
{
    bmpInfoHeader.width = width;
    bmpInfoHeader.height = height;
    bmpInfoHeader.size = sizeof(BMPInfoHeader);
    fileHeader.offsetData = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);
    bmpInfoHeader.bitCount = 24;
    bmpInfoHeader.compression = 0;
    fileHeader.fileSize = fileHeader.offsetData + data.size() + bmpInfoHeader.height;
}

void BMP::WriteHeadersAndData(const char *fname) 
{
    std::ofstream of{ fname, std::ios_base::binary };
    of.write((const char*)&fileHeader, sizeof(fileHeader));
    of.write((const char*)&bmpInfoHeader, sizeof(bmpInfoHeader));
    of.write((const char*)data.data(), data.size());
}
