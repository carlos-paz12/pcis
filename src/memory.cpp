#include "memory.h"
#include <stdexcept>

Memory::Memory(size_t size) : data(size, 0) {}

int Memory::read(size_t address) {
    if (address >= data.size()) {
        throw std::out_of_range("Memory read out of bounds");
    }
    return data[address];
}

void Memory::write(size_t address, int value) {
    if (address >= data.size()) {
        throw std::out_of_range("Memory write out of bounds");
    }
    data[address] = value;
}

void Memory::loadProgram(const std::vector<int>& program) {
    if (program.size() > data.size()) {
        throw std::out_of_range("Program size exceeds memory size");
    }
    std::copy(program.begin(), program.end(), data.begin());
}