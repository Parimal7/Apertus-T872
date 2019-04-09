#include "BMP.hpp"

#include <fstream>

BMP::BMP(uint32_t width, uint32_t height) 
{
    bmpMagicNumber.magic[0] = 'B';
    bmpMagicNumber.magic[1] = 'M';
    bmpInfoHeader.width = width;
    bmpInfoHeader.height = height;
    bmpInfoHeader.size = sizeof(bmpInfoHeader);
    fileHeader.offsetData = sizeof(bmpInfoHeader) + sizeof(fileHeader) + sizeof(bmpMagicNumber);
    bmpInfoHeader.bitCount = 24;
    bmpInfoHeader.compression = 0;
    fileHeader.fileSize = fileHeader.offsetData + 3 * IMAGE_SIZE + bmpInfoHeader.height;
}

BMP::~BMP()
{
    delete[] data;
}

void BMP::GetData(uint8_t * channel)
{
    for(long long index = 0; index < 3 * IMAGE_SIZE; index = index + 3)
    {
        long long currentRow = index / (3 * WIDTH);
        uint8_t R = channel[(HEIGHT - currentRow - 1) * (3 * WIDTH) + (index % (3 * WIDTH))];
        uint8_t G = channel[(HEIGHT - currentRow - 1) * (3 * WIDTH) + (index % (3 * WIDTH)) + 1];
        uint8_t B = channel[(HEIGHT - currentRow - 1) * (3 * WIDTH) + (index % (3 * WIDTH)) + 2];
        data[index] = B;
        data[index + 1] = G;
        data[index + 2] = R; 
    }
}

void BMP::WriteToFile(std::string fileName) 
{
    std::ofstream of{ fileName, std::ios_base::binary };
    of.write((const char*)&bmpMagicNumber, sizeof(bmpMagicNumber));
    of.write((const char*)&fileHeader, sizeof(fileHeader));
    of.write((const char*)&bmpInfoHeader, sizeof(bmpInfoHeader));
    of.write(reinterpret_cast<const char*>(data), 3 * IMAGE_SIZE);
}
