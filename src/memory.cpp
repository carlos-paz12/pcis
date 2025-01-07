#include <stdexcept>

#include "../inc/memory.h"

memory::memory(size_t size) : data(size, 0) {}

int memory::read(size_t address) {
    if (address >= data.size()) {
        throw std::out_of_range("memory read out of bounds");
    }
    return data[address];
}

void memory::write(size_t address, int value) {
    if (address >= data.size()) {
        throw std::out_of_range("memory write out of bounds");
    }
    data[address] = value;
}

void memory::loadProgram(const std::vector<int>& program) {
    if (program.size() > data.size()) {
        throw std::out_of_range("Program size exceeds memory size");
    }
    std::copy(program.begin(), program.end(), data.begin());
}