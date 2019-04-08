#include "Debayer.hpp"

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
      std::cout << "Invalid command! Correct Usage: ./main filename\n";
      return -1;
    }
    
    std::string fileName = argv[1];

    Debayer image(fileName);

    std::cout << "Loading RAW file into 12 bit buffer...\n\n";
    image.LoadFile();

    std::cout << "Converting 12 bit buffer to 8 bit...\n\n";
    image.ConvertTo8Bits();

    std::cout << "Extracting into 4 channels...\n\n";
    image.ExtractChannels();

    image.PrintIntensity();

    std::cout << "Debayering using linear interpolation...\n";
    image.DebayerImage();
    
    std::cout << "Converting channels to PPM files...\n";
    image.ConvertToPPM();

    std::cout << "Converting PPM to BMP file...\n";
    image.ConvertToBMP();

    std::cout << "Sucess!\n";
    return 0;
}