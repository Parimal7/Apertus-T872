#include "Debayer.hpp"
using namespace std;

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
      cout << "Invalid command! Correct Usage: ./main filename\n";
      return -1;
    }
    
    string fileName = argv[1];

    Debayer image(fileName);

    cout << "Loading RAW file into 12 bit buffer...\n\n";
    image.LoadFile();

    cout << "Converting 12 bit buffer to 8 bit...\n\n";
    image.ConvertTo8Bits();

    cout << "Extracting into 4 channels...\n\n";
    image.ExtractChannels();

    image.PrintIntensity();

    cout << "Debayering using linear interpolation...\n";
    image.DebayerImage();
    
    cout << "Converting channels to PPM files...\n";
    image.ConvertToPPM();

    cout << "Converting PPM to BMP file...\n";
    image.ConvertToBMP();

    cout << "Sucess!\n";
    return 0;
}
