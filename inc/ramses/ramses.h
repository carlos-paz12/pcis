#ifndef RAMSES_H
#define RAMSES_H

class Ramses {
public:
    // Method to add two 8-bit variables
    static unsigned char add8Bits(unsigned char a, unsigned char b);

    // Method to add two 16-bit variables
    static unsigned short add16Bits(unsigned short a, unsigned short b);

    // Method to subtract two 8-bit variables
    static unsigned char subtract8Bits(unsigned char a, unsigned char b);

    // Method to determine the largest value in a vector of 32 positions
    static unsigned char maxValue(unsigned char* vector, int size);

    // Method to call the 16-bit addition subroutine
    static unsigned short callAdd16Bits(unsigned short a, unsigned short b);
};

#endif // RAMSES_H