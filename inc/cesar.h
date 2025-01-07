#ifndef CESAR_H
#define CESAR_H

class Cesar {
public:
    // Method to add two 8-bit variables
    static unsigned char add8Bits(unsigned char a, unsigned char b);

    // Method to add two 16-bit variables
    static unsigned short add16Bits(unsigned short a, unsigned short b);

    // Method to subtract two 8-bit variables
    static unsigned char subtract8Bits(unsigned char a, unsigned char b);

    // Method to determine the largest value in a vector of 32 positions
    static unsigned char maxValue(unsigned char* vector, int size);
};

#endif // CESAR_H