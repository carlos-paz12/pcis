#include <bits/stdc++.h>
#include <chrono>
#include "../inc/utils.h"
#include "../inc/cesar/cesar.h"
#include "../inc/neander/Neander.hpp"
#include "../inc/ramses/ramses.h"


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

void loadMemoryData(Memoria& memoria, const std::string& dataFile){
  std::ifstream infile(dataFile);
  int adress, value;
  while(infile >> adress >> value){
    memoria.write()
  }
}

void loadMemoryInstruct(Memoria& memoria, const std::string& instrutionFile){
  int address, dataAddress;
  std::string opcode;
  while (infile >> address >> opcode >> dataAddress) {
    if (opcode == "ADD") {
     memoria.write(address, Instrucao(Opcode::ADD_END, dataAddress).to_uint8());
    }
    else if(){} // ... Continuo já ! só resolver uma coisa Ç:
}
}


int main() {
  
  ProcessorType processor = selectP();
  if (processor == INVALID) {
    std::cerr << "Invalid Processor" << std::endl;
    return 1;
  }

std::string dataFile, instructionFile;
  std::cout << "Enter the data file path: ";
  std::cin >> dataFile;
  std::cout << "Enter the instruction file path: ";
  std::cin >> instructionFile;

  Memoria memoria;
  loadMemoryData(memoria, dataFile);
  loadMemoryInstructions(memoria, instructionFile);

  auto start = std::chrono::high_resolution_clock::now();

  switch (processor) {
  case CESAR:
    std::cou << "Operations with Cesar"
    std::cout << "Cesar:" << std::endl;
    // std::cout << "8-bit addition: " << (int)Cesar::add8Bits(a, b) << std::endl;
    // std::cout << "16-bit addition: " << Cesar::add16Bits(c, d) << std::endl;
    // std::cout << "8-bit subtraction: " << (int)Cesar::subtract8Bits(b, a) << std::endl;
    break;
  case NEANDER:
    // Operations with Neander
    std::cout << "\nNeander:" << std::endl;
    Neander processador(memoria);
    processador.fetch_decode_execute();
    break;
    //std::cout << "8-bit addition: " << (int)Neander::add8Bits(a, b) << std::endl;
    //std::cout << "8-bit subtraction: " << (int)Neander::subtract8Bits(b, a) << std::endl;
    //std::cout << "16-bit addition: " << Neander::add16Bits(c, d) << std::endl;
  case RAMSES:
    // Operations with Ramses
    std::cout << "\nRamses:" << std::endl;
    // std::cout << "8-bit addition: " << (int)Ramses::add8Bits(a, b) << std::endl;
    // std::cout << "16-bit addition: " << Ramses::add16Bits(c, d) << std::endl;
    // std::cout << "8-bit subtraction: " << (int)Ramses::subtract8Bits(b, a)<< std::endl;
    break;
  default:
    std::cerr << "Invalid Processor" << std::endl;
    return 1;
  }

  
  
  

  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end - start;
  int cycles = static_cast<int>(elapsed.count() * 1e6);

  std::ofstream outfile("data/time_results.txt");
  outfile << ("Processor: ")
          << (processor == CESAR     ? "Cesar"
              : processor == NEANDER ? "Neander"
                                     : "Ramses")
          << std::endl;
  outfile << "Execution time: " << cycles << " cycles" << std::endl;
  outfile.close();
  return 0;
}