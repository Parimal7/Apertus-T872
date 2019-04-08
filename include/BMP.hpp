#ifndef BMP_H
#define BMP_H

#include "BMP_Headers.hpp"
#include "Debayer.hpp"

#include <string>

class BMP 
{
	BMPMagicNumber bmpMagicNumber;
    BMPFileHeader fileHeader;
    BMPInfoHeader bmpInfoHeader;
    BMPColorHeader bmpColorHeader;
    uint8_t * data = new uint8_t[3 * IMAGE_SIZE];

public:

    BMP(uint32_t width, uint32_t height);
    void GetData(uint8_t * channel);
    void WriteToFile(std::string fileName);
};

#endif