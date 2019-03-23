# APERTUS C/C++ CHALLENGE

My solution for the T872 qualification challenge.

## The Challenge

- [x] Write a C/CPP program for loading a RAW12 image ([portrait-gainx2-offset2047-20ms-02.raw12](http://files.apertus.org/AXIOM-Beta/snapshots/portraits/portrait-gainx2-offset2047-20ms-02.raw12)) into the memory - separate the 4 channels (in memory - 8 bits). Output the intensity values of the first 5x5 pixels (square tile) R, G, G, B channels.

- [x] Save the channels (separately) as valid image files (8 bits per pixel) named appropriately without use of any external libraries (e.g. openJPG/lodePNG). (Hint: PPM file format).

- [x] Debayer the CFA ([color filter array](https://en.wikipedia.org/wiki/Color_filter_array)) data (in memory using nearest neighbour / bilinear) - output the image as a valid image file (8-bit, without use of any external library).

Additional task(for [T763](https://lab.apertus.org/T763))-

- [x] Save the debayered RGB image as a BMP file (without use of any external libraries) - expected that you create the BMP file from scratch. As an alternative, you can save the image as a single frame in an AVI file without use of external libraries (bonus points).



## Bonus points for 
- [x] Use cmake for building the C/CPP program.
- [x] Abide by the C/CPP coding guidelines (https://gist.github.com/lefticus/10191322) and project structuring (create appropriate directories, header files, c/cpp files to modularize the code in meaningful ways).
- [x] If you can load part of your program as a dynamic library (.so file)
- [ ] If you use a nonlinear curve for the 12 to 8 bit conversion, without ignoring the bottom 4 bits (lots of different solutions possible) and explain your choice (why did you choose that curve).

## Instructions for Linux environment 

1) `git clone https://github.com/Parimal7/Apertus-T872.git`
2) `cd Apertus-T872`
3) `mkdir build && cd build` 
5) `cmake ..`
6) `make`
7) `./RAWtoPPM ../test.raw12`

The output ppm files are stored in the build directory by the name -
1) red.ppm
2) green0.ppm
3) green1.ppm
4) blue.ppm
5) color.ppm
6) color.bmp


