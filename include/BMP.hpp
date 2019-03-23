#ifndef BMP_H
#define BMP_H

#include "BMP_Headers.hpp"
#include <vector>

class BMP 
{
public:

    BMPFileHeader fileHeader;
    BMPInfoHeader bmpInfoHeader;
    BMPColorHeader bmpColorHeader;
    std::vector<uint8_t> data;

    BMP(uint32_t width, uint32_t height);

    void WriteHeadersAndData(const char *fname);
};

#endif
