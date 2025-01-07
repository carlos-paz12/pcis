#ifndef NEANDER_H
#define NEANDER_H

class Neander {
public:
    // Method to add two 8-bit variables
    static unsigned char add8Bits(unsigned char a, unsigned char b);

    // Method to subtract two 8-bit variables
    static unsigned char subtract8Bits(unsigned char a, unsigned char b);

    // Method to add two 16-bit variables (only for Ramses and Cesar)
    static unsigned short add16Bits(unsigned short a, unsigned short b);

    // Method to determine the largest value in an array of 32 positions
    static unsigned char maxValue(unsigned char* array, int size);
};

#endif // NEANDER_H