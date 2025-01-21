#include "utils.h"
#include <iostream>

void printRegisters(int registers[], int size) {
    std::cout << "Registers: ";
    for (int i = 0; i < size; ++i) {
        std::cout << registers[i] << " ";
    }
    std::cout << std::endl;
}

void printMemory(int memory[], int size) {
    std::cout << "Memory: ";
    for (int i = 0; i < size; ++i) {
        std::cout << memory[i] << " ";
    }
    std::cout << std::endl;
}

void printFlags(int flags) {
    std::cout << "Flags: " << flags << std::endl;
}

void printExecutionTime(int cycles) {
    std::cout << "Execution Time: " << cycles << " cycles" << std::endl;
}