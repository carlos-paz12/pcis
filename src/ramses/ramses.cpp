#ifndef RAMSES_CPP
#define RAMSES_CPP

#include "../../inc/ramses/ramses.h"

// Implementation of the method to add two 8-bit variables
unsigned char Ramses::add8Bits(unsigned char a, unsigned char b) {
  return a + b;
}

// Implementation of the method to add two 16-bit variables
unsigned short Ramses::add16Bits(unsigned short a, unsigned short b) {
  return a + b;
}

// Implementation of the method to subtract two 8-bit variables
unsigned char Ramses::subtract8Bits(unsigned char a, unsigned char b) {
  return a - b;
}

// Implementation of the method to determine the largest value in an array of 32
// positions
unsigned char Ramses::maxValue(unsigned char *array, int size) {
  unsigned char max = array[0];
  for (int i = 1; i < size; i++) {
    if (array[i] > max) {
      max = array[i];
    }
  }
  return max;
}

// Implementation of the method to call the 16-bit addition subroutine
unsigned short Ramses::callAdd16Bits(unsigned short a, unsigned short b) {
  return add16Bits(a, b);
}

#endif // RAMSES_CPP