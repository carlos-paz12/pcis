#include <bits/stdc++.h>
#include "../inc/cesar/cesar.h"
#include "../inc/neander/Neander.hpp"
//#include "../inc/ramses/ramses.h"

enum ProcessorType
{
  NEANDER,
  CESAR,
  RAMSES,
  INVALID
};

// Function to select the processor
ProcessorType selectP()
{
  std::string choice;
  std::cout << "Select the processor you want to execute (neander, cesar, ramses): ";
  std::cin >> choice;

  if (choice == "neander" || choice == "NEANDER")
  {
    return NEANDER;
  }
  else if (choice == "cesar" || choice == "CESAR")
  {
    return CESAR;
  }
  else if (choice == "ramses" || choice == "RAMSES")
  {
    return RAMSES;
  }
  else
  {
    return INVALID;
  }
}

// Function to load data into memory
void loadMemoryData(Memoria &memoria, const std::string &dataFile)
{
  std::ifstream infile(dataFile);
  int address, value;

  // Carregar os dados na memória
  while (infile >> address >> value)
  {
    std::cout << "Escrevendo " << value << " no endereço " << address << std::endl;
    memoria.escreve(address, value);
  }
}

// Function to load instructions into memory
void loadMemoryInstructions(Memoria &memoria, const std::string &instrutionFile)
{
  std::ifstream infile(instrutionFile);
  int dataAddress;
  std::string opcode;
  std::vector<Instrucao> programa;
  while (infile >> opcode >> dataAddress)
  {
    std::cout << "Escrevendo " << opcode << " mirando no endereço " << dataAddress << std::endl;
    if (opcode == "NOP")
    {
      programa.push_back(Instrucao(Opcode::NOP, dataAddress));
    }
    else if (opcode == "STA")
    {
      programa.push_back(Instrucao(Opcode::STA_END, dataAddress));
    }
    else if (opcode == "LDA")
    {
      programa.push_back(Instrucao(Opcode::LDA_END, dataAddress));
    }
    else if (opcode == "ADD")
    {
      programa.push_back(Instrucao(Opcode::ADD_END, dataAddress));
    }
    else if (opcode == "AND")
    {
      programa.push_back(Instrucao(Opcode::AND_END, dataAddress));
    }
    else if (opcode == "OR")
    {
      programa.push_back(Instrucao(Opcode::OR_END, dataAddress));
    }
    else if (opcode == "NOT")
    {
      programa.push_back(Instrucao(Opcode::NOT, dataAddress));
    }
    else if (opcode == "JMP")
    {
      programa.push_back(Instrucao(Opcode::JMP_END, dataAddress));
    }
    else if (opcode == "JN")
    {
      programa.push_back(Instrucao(Opcode::JN_END, dataAddress));
    }
    else if (opcode == "JZ")
    {
      programa.push_back(Instrucao(Opcode::JZ_END, dataAddress));
    }
    else if (opcode == "HLT")
    {
      programa.push_back(Instrucao(Opcode::HLT, dataAddress));
    }
      else if(opcode == "MUX")
    {
      programa.push_back(Instrucao(Opcode::MUX, dataAddress));
    }
  }

  memoria.carrega(programa);
}


int main(int argc, char const *argv[])
{
  // Select processor
  ProcessorType processor = NEANDER;
  if (processor == INVALID)
  {
    std::cerr << "Invalid Processor" << std::endl;
    return 1;
  }

  // Get file paths for data and instructions
  std::string dataFile = argv[1], instructionFile = argv[2];
  //std::cout << "Enter the data file path: ";
  // std::cin >> instructionFile;
  //std::cout << "Enter the instruction file path: ";
  

  Memoria memoria;

  loadMemoryData(memoria, dataFile);
  loadMemoryInstructions(memoria, instructionFile);

  auto start = std::chrono::high_resolution_clock::now();

  // Initialize and run processor
  switch (processor)
  {
  case NEANDER:
  {
    // Neander processor logic
    std::cout << "\nNeander Processor:" << std::endl;
    Neander neanderProcessor(memoria);       // Initialize Neander processor
    neanderProcessor.fetch_decode_execute(); // Call its execution function
    break;
  }
  case CESAR:
    // Implement CESAR processor logic here
    std::cout << "\nCesar Processor: (Not yet implemented)" << std::endl;
    break;
  case RAMSES:
    // Implement RAMSES processor logic here
    std::cout << "\nRamses Processor: (Not yet implemented)" << std::endl;
    break;
  default:
    std::cerr << "Invalid Processor" << std::endl;
    return 1;
  }


  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end - start;
  int cycles = static_cast<int>(elapsed.count() * 1e6); // Calculate time in microseconds

  // Output results to a file
  std::ofstream outfile("data/time_results.txt");
  outfile << "Processor: " << (processor == CESAR ? "Cesar" : processor == NEANDER ? "Neander"
                                                                                   : "Ramses")
          << std::endl;
  outfile << "Execution time: " << cycles << " cycles" << std::endl;
  outfile.close();

  return 0;
}
