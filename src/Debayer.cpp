#include "Debayer.hpp"

#include "BMP.hpp"

Debayer::Debayer(std::string fileName)
{
    this->fileName = fileName;
}

void Debayer::LoadFile()
{
    std::ifstream rawFile(fileName, std::ifstream::binary);
    rawFile.read(reinterpret_cast<char*>(buffer12Bits), IMAGE_SIZE * 3 / 2);
    rawFile.close();
}

void Debayer::ConvertTo8Bits()
{
    int j = 0;
    uint32_t bufferSize = IMAGE_SIZE * 3 / 2;
    for (long long index = 0; index < bufferSize; index += 3)
    {
        buffer8Bits[j]   = buffer12Bits[index];
        buffer8Bits[j+1] = ((buffer12Bits[index+1] & 0x0F) << 4) | (buffer12Bits[index+2] >> 4);
        j+=2;
    }

    delete[] buffer12Bits;
}

void Debayer::ExtractChannels()
{
    int odd = 0, even = 0;
    for (long long index = 0; index < IMAGE_SIZE; index += 2) 
    {
        if ((index % DOUBLE_WIDTH) < WIDTH) 
        {
            redChannel[even]      = buffer8Bits[index];
            green0Channel[even]   = buffer8Bits[index + 1];
            even++;
        } 
        else 
        {
            green1Channel[odd]    = buffer8Bits[index];
            blueChannel[odd]      = buffer8Bits[index + 1];
            odd++;
        }
    }
}

void Debayer::GetIntensity(uint8_t * channel)
{
    for (int index = 0; index < 5; index++)
    {
        std::cout << std::hex << unsigned(channel[4096 * index + 0]) << " ";
        std::cout << std::hex << unsigned(channel[4096 * index + 1])<< " ";
        std::cout << std::hex << unsigned(channel[4096 * index + 2])<< " ";
        std::cout << std::hex << unsigned(channel[4096 * index + 3])<< " ";
        std::cout << std::hex << unsigned(channel[4096 * index + 4])<< " ";
        std::cout << std::endl;
    }
     
    std::cout << std::endl;
}

void Debayer::PrintIntensity()
{
    std::cout << "Intensity values for 5 x 5 redChannel is \n";
    GetIntensity(redChannel);
    std::cout << "Intensity values for 5 x 5 green0Channel is \n";
    GetIntensity(green0Channel);
    std::cout << "Intensity values for 5 x 5 green1Channel is \n";
    GetIntensity(green1Channel);
    std::cout << "Intensity values for 5 x 5 blueChannel is \n";
    GetIntensity(blueChannel);
}

void Debayer::ChannelToPPM(uint8_t * channel, std::string fileName)
{
    std::ofstream outfile(fileName);

    if(fileName == "color.ppm")
    {
        outfile << "P3" << "\n" << WIDTH << " " << HEIGHT << "\n" << 255 << "\n";
        for(long long index = 0; index < 3 * IMAGE_SIZE; index += 3)
        {
            if(index % WIDTH == 0 && index > 0)
            {
                outfile << "\n";
            }
            int r = colorChannel[index];
            int g = colorChannel[index+1];
            int b = colorChannel[index+2];
            outfile << r << " " << g << " " << b << " ";
        }        
    }

    else
    {
        outfile << "P3" << "\n" << WIDTH / 2 << " " << HEIGHT/2 << "\n" << 255 << "\n";
        for(long long index = 0; index < QUARTER_SIZE; ++index)
        {
            int c = channel[index];
            if( index % WIDTH/2 == 0 && index > 0)
            {
                outfile << "\n";
            }
            if(fileName == "red.ppm")
            {
                outfile << c << " " << 0 << " " << 0 << " ";
            }
            if(fileName == "green0.ppm")
            {
                outfile << 0 << " " << c << " " << 0 << " ";
            }
            if(fileName == "green1.ppm")
            {
                outfile << 0 << " " << c << " " << 0 << " ";
            }
            if(fileName == "blue.ppm")
            {
                outfile << 0 << " " << 0 << " " << c << " ";
            }
        }
    }
}

void Debayer::ConvertToPPM()
{
    ChannelToPPM(redChannel, "red.ppm");
    ChannelToPPM(green0Channel, "green0.ppm");
    ChannelToPPM(green1Channel, "green1.ppm");
    ChannelToPPM(blueChannel, "blue.ppm");
    ChannelToPPM(colorChannel, "color.ppm");
}

void Debayer::DebayerImage()
{
    int tripleIndex;
    for (long long index = 0; index < IMAGE_SIZE; index += 2)
    {
        tripleIndex = index * 3;
        if ((index % DOUBLE_WIDTH) < WIDTH) 
        {
            colorChannel[tripleIndex    ] = buffer8Bits[index];
            colorChannel[tripleIndex + 1] = buffer8Bits[index + 1];
            colorChannel[tripleIndex + 2] = buffer8Bits[index + WIDTH + 1];
            colorChannel[tripleIndex + 3] = buffer8Bits[index];
            colorChannel[tripleIndex + 4] = buffer8Bits[index + 1];
            colorChannel[tripleIndex + 5] = buffer8Bits[index + WIDTH + 1];
        } 
        else 
        {
            colorChannel[tripleIndex    ] = buffer8Bits[index - WIDTH];
            colorChannel[tripleIndex + 1] = buffer8Bits[index];
            colorChannel[tripleIndex + 2] = buffer8Bits[index + 1];
            colorChannel[tripleIndex + 3] = buffer8Bits[index - WIDTH];
            colorChannel[tripleIndex + 4] = buffer8Bits[index];
            colorChannel[tripleIndex + 5] = buffer8Bits[index + 1];
        }
    }
}

void Debayer::ConvertToBMP()
{
    BMP bmp1(WIDTH,HEIGHT);
    bmp1.GetData(colorChannel);
    bmp1.WriteToFile("color.bmp");
}