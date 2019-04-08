#ifndef DEBAYER_H
#define DEBAYER_H

#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>

const uint16_t WIDTH = 4096;
const uint16_t HEIGHT = 3072;
const uint16_t DOUBLE_WIDTH = WIDTH << 1;
const uint32_t IMAGE_SIZE = WIDTH * HEIGHT;
const uint32_t QUARTER_SIZE = IMAGE_SIZE >> 2;

class Debayer
{
    std::string fileName;
  
    uint8_t * buffer12Bits = new uint8_t[IMAGE_SIZE * 3 / 2];
    uint8_t * buffer8Bits = new uint8_t[IMAGE_SIZE];
    uint8_t * redChannel = new uint8_t[QUARTER_SIZE];
    uint8_t * green0Channel = new uint8_t[QUARTER_SIZE];
    uint8_t * green1Channel = new uint8_t[QUARTER_SIZE];
    uint8_t * blueChannel = new uint8_t[QUARTER_SIZE];
    uint8_t * colorChannel = new uint8_t[IMAGE_SIZE * 3];

public:

    Debayer(std::string fileName);

    void LoadFile();

    void ConvertTo8Bits();
    
    void ExtractChannels();
    
    void GetIntensity(uint8_t * channel);
    
    void PrintIntensity();
    
    void ChannelToPPM(uint8_t * channel, std::string fileName);
    
    void ConvertToPPM();
    
    void DebayerImage();

    void ConvertToBMP();

    void FreeUpSpace();
};

#endif