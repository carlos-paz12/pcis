#ifndef CESAR_CPP
#define CESAR_CPP

#include "../inc/cesar.h"

// Implementation of the method to add two 8-bit variables
unsigned char Cesar::add8Bits(unsigned char a, unsigned char b) {
    return a + b;
}

// Implementation of the method to add two 16-bit variables
unsigned short Cesar::add16Bits(unsigned short a, unsigned short b) {
    return a + b;
}

// Implementation of the method to subtract two 8-bit variables
unsigned char Cesar::subtract8Bits(unsigned char a, unsigned char b) {
    return a - b;
}

// Implementation of the method to determine the largest value in a vector of 32 positions
unsigned char Cesar::maxValue(unsigned char* vector, int size) {
    unsigned char max = vector[0];
    for (int i = 1; i < size; i++) {
        if (vector[i] > max) {
            max = vector[i];
        }
    }
    return max;
}

#endif // CESAR_CPP