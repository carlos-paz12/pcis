#include "../../inc/utils.h"
#include "../inc/cesar/cesar.h"
#include "../inc/neander/Neander.hpp"
#include "../inc/ramses/ramses.h"
#include <bits/stdc++.h>

enum ProcessorType { NEANDER, CESAR, RAMSES, INVALID };

ProcessorType selectP() {
  std::string choice;
  std::cout << "Select the processor you want to execute" << std::endl;
  std::cin >> choice;

  if (choice == "neander" || choice == "NEANDER") {
    return NEANDER;
  } else if (choice == "cesar" || choice == "CESAR") {
    return CESAR;
  } else if (choice == "ramses" || choice == "RAMSES")
    return RAMSES;
  else {
    return INVALID;
  }
}

int main() {
  ProcessorType processor = selectP();
  if (processor == INVALID) {
    std::cerr << "Invalid Processor" << std::endl;
    return 1;
  }
  // Example of using the classes and methods
  unsigned char a = 10, b = 20;
  unsigned short c = 30000, d = 10000;
  auto start = std::chrono::high_resolution_clock::now();

  switch (processor) {
  case CESAR:
    // Operations with Cesar
    std::cout << "Cesar:" << std::endl;
    std::cout << "8-bit addition: " << (int)Cesar::add8Bits(a, b) << std::endl;
    // std::cout << "16-bit addition: " << Cesar::add16Bits(c, d) << std::endl;
    std::cout << "8-bit subtraction: " << (int)Cesar::subtract8Bits(b, a)
              << std::endl;
    break;
  case NEANDER:
    // Operations with Neander
    std::cout << "\nNeander:" << std::endl;
    std::cout << "8-bit addition: " << (int)Neander::add8Bits(a, b)
              << std::endl;
    std::cout << "8-bit subtraction: " << (int)Neander::subtract8Bits(b, a)
              << std::endl;
    std::cout << "16-bit addition: " << Neander::add16Bits(c, d) << std::endl;

  case RAMSES:
    // Operations with Ramses
    std::cout << "\nRamses:" << std::endl;
    std::cout << "8-bit addition: " << (int)Ramses::add8Bits(a, b) << std::endl;
    std::cout << "16-bit addition: " << Ramses::add16Bits(c, d) << std::endl;
    std::cout << "8-bit subtraction: " << (int)Ramses::subtract8Bits(b, a)
              << std::endl;
  default:
    std::cerr << "Invalid Processor" << std::endl;
    return 1;
  }

  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end - start;
  int cycles = static_cast<int>(elapsed.count() * 1e6);
  // Example of using utility functions
  int registers[4] = {1, 2, 3, 4};
  int memory[4] = {10, 20, 30, 40};
  int flags = 0b0001; // Example of flags

  printRegisters(registers, 4);
  printMemory(memory, 4);
  printFlags(flags);
  printExecutionTime(cycles);

  std::ofstream outfile("time_results.txt");
  outfile << ("Processor: ")
          << (processor == CESAR     ? "Cesar"
              : processor == NEANDER ? "Neander"
                                     : "Ramses")
          << std::endl;
  outfile << "Execution time: " << cycles << " cycles" << std::endl;
  outfile.close();
  return 0;
}