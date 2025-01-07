#include <iostream>
#include "../../inc/neander.h"
#include "../../inc/cesar.h"
#include "../../inc/ramses.h"
#include "../../inc/utils.h"

int main() {
    // Example of using the classes and methods
    unsigned char a = 10, b = 20;
    unsigned short c = 30000, d = 10000;

    // Operations with Cesar
    std::cout << "Cesar:" << std::endl;
    std::cout << "8-bit addition: " << (int)Cesar::add8Bits(a, b) << std::endl;
    std::cout << "16-bit addition: " << Cesar::add16Bits(c, d) << std::endl;
    std::cout << "8-bit subtraction: " << (int)Cesar::subtract8Bits(b, a) << std::endl;

    // Operations with Neander
    std::cout << "\nNeander:" << std::endl;
    std::cout << "8-bit addition: " << (int)Neander::add8Bits(a, b) << std::endl;
    std::cout << "8-bit subtraction: " << (int)Neander::subtract8Bits(b, a) << std::endl;
    std::cout << "16-bit addition: " << Neander::add16Bits(c, d) << std::endl;

    // Operations with Ramses
    std::cout << "\nRamses:" << std::endl;
    std::cout << "8-bit addition: " << (int)Ramses::add8Bits(a, b) << std::endl;
    std::cout << "16-bit addition: " << Ramses::add16Bits(c, d) << std::endl;
    std::cout << "8-bit subtraction: " << (int)Ramses::subtract8Bits(b, a) << std::endl;

    // Example of using utility functions
    int registers[4] = {1, 2, 3, 4};
    int memory[4] = {10, 20, 30, 40};
    int flags = 0b0001; // Example of flags
    int cycles = 100; // Example of execution time

    printRegisters(registers, 4);
    printMemory(memory, 4);
    printFlags(flags);
    printExecutionTime(cycles);

    return 0;
}