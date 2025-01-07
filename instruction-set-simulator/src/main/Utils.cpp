#include "Utils.h"
#include <iostream>

void printRegisters(int registers[], int size) {
    std::cout << "Registradores: ";
    for (int i = 0; i < size; ++i) {
        std::cout << "R" << i << ": " << registers[i] << " ";
    }
    std::cout << std::endl;
}

void printMemory(int memory[], int size) {
    std::cout << "Memória: ";
    for (int i = 0; i < size; ++i) {
        std::cout << "M" << i << ": " << memory[i] << " ";
    }
    std::cout << std::endl;
}

void printFlags(int flags) {
    std::cout << "Flags: " << std::bitset<8>(flags) << std::endl;
}

void printExecutionTime(int cycles) {
    std::cout << "Tempo de execução: " << cycles << " ciclos" << std::endl;
}